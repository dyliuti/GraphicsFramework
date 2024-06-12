#include "systemstatus.h"
#include "systemstatus_linux.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <EeoCompatDecl>
#include <QBasicTimer>
#include <QFileInfo>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#define PRINT_INTERVAL 20

//////////////////////////////////////////////////////////////////
///
///
///
///
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

#define VMRSS_LINE 17
#define VMSIZE_LINE 13
#define PROCESS_ITEM 14

typedef struct {
    unsigned int pid;
    unsigned long utime;  //user time
    unsigned long stime;  //kernel time
    unsigned long cutime; //all user time
    unsigned long cstime; //all dead time
}Proc_Cpu_Occupy_t;



typedef struct CPUPACKED         //定义一个cpu occupy的结构体
{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned int user; //定义一个无符号的int类型的user
    unsigned int nice; //定义一个无符号的int类型的nice
    unsigned int system;//定义一个无符号的int类型的system
    unsigned int idle; //定义一个无符号的int类型的idle
    unsigned int lowait;
    unsigned int irq;
    unsigned int softirq;
}CPU_OCCUPY;

//获取第N项开始的指针
const char* get_items(const char*buffer ,unsigned int item){

    const char *p =buffer;

    int len = strlen(buffer);
    int count = 0;

    for (int i=0; i<len;i++){
        if (' ' == *p){
            count ++;
            if(count == item -1){
                p++;
                break;
            }
        }
        p++;
    }

    return p;
}


//获取总的CPU时间
unsigned long get_cpu_total_occupy(){

    FILE *fd;
    char buff[1024]={0};
    CPU_OCCUPY t;

    fd =fopen("/proc/stat","r");
    if (nullptr == fd){
        return 0;
    }

    fgets(buff,sizeof(buff),fd);
    char name[64]={0};
    sscanf(buff,"%s %ld %ld %ld %ld",name,&t.user,&t.nice,&t.system,&t.idle);
    fclose(fd);

    return (t.user + t.nice + t.system + t.idle);
}


//获取进程的CPU时间
unsigned long get_cpu_proc_occupy(unsigned int pid){

    char file_name[64]={0};
    Proc_Cpu_Occupy_t t;
    FILE *fd;
    char line_buff[1024]={0};
    sprintf(file_name,"/proc/%d/stat",pid);

    fd = fopen(file_name,"r");
    if(nullptr == fd){
        return 0;
    }

    fgets(line_buff,sizeof(line_buff),fd);

    sscanf(line_buff,"%u",&t.pid);
    const char *q =get_items(line_buff,PROCESS_ITEM);
    sscanf(q,"%ld %ld %ld %ld",&t.utime,&t.stime,&t.cutime,&t.cstime);
    fclose(fd);

    return (t.utime + t.stime + t.cutime + t.cstime);
}


//获取CPU占用率
float get_proc_cpu(unsigned int pid){

    unsigned long totalcputime1,totalcputime2;
    unsigned long procputime1,procputime2;

    totalcputime1=get_cpu_total_occupy();
    procputime1=get_cpu_proc_occupy(pid);

    usleep(200000);

    totalcputime2=get_cpu_total_occupy();
    procputime2=get_cpu_proc_occupy(pid);

    float pcpu = 0.0;
    if(0 != totalcputime2-totalcputime1){
        pcpu=100.0 * (procputime2-procputime1)/(totalcputime2-totalcputime1);
    }

    return pcpu;
}

//进程本身
int get_pid(const char* process_name, const char* user = nullptr)
{
    if(user == nullptr){
        user = getlogin();
    }

    char cmd[512];
    if (user){
        sprintf(cmd, "pgrep %s -u %s", process_name, user);
    }

    FILE *pstr = popen(cmd,"r");

    if(pstr == nullptr){
        return 0;
    }

    char buff[512];
    ::memset(buff, 0, sizeof(buff));
    if(NULL == fgets(buff, 512, pstr)){
        return 0;
    }

    return atoi(buff);
}

int get_cpuoccupy(CPU_OCCUPY *cpust) //对无类型get函数含有一个形参结构体类弄的指针O
{
    FILE *fd;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy = cpust;

    fd = fopen("/proc/stat", "r");
    fgets(buff, sizeof(buff), fd);

    sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle, &cpu_occupy->lowait, &cpu_occupy->irq, &cpu_occupy->softirq);


    fclose(fd);

    return 0;
}


double cal_cpuoccupy(CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    unsigned long od, nd;
    double cpu_use = 0;

    od = (unsigned long)(o->user + o->nice + o->system + o->idle + o->lowait + o->irq + o->softirq);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (unsigned long)(n->user + n->nice + n->system + n->idle + n->lowait + n->irq + n->softirq);//第二次(用户+优先级+系统+空闲)的时间再赋给od
    double sum = nd - od;
    double idle = n->idle - o->idle;
    cpu_use = idle / sum;
    idle = n->user + n->system + n->nice - o->user - o->system - o->nice;
    cpu_use = idle / sum;
    return cpu_use;
}

SystemStatusPrivate::SystemStatusPrivate(QObject *parent)
    : SystemStatusBasePrivate(parent)
{
}

SystemStatusPrivate::~SystemStatusPrivate()
{
}

QPair<float, float> SystemStatusPrivate::getCpuInfo()
{
    return getCpuUsePercentage();
}

float SystemStatusPrivate::getSysMemUsePercentage()
{
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        std::cerr << "Failed to open /proc/meminfo" << std::endl;
        return 0.0;
    }

    std::string line;
    long long totalMemory = 0;
    long long freeMemory = 0;
    long long buffers = 0;
    long long cached = 0;

    while (std::getline(meminfo, line)) {
        std::istringstream iss(line);
        std::string key;
        long long value;

        if (iss >> key >> value) {
            if (key == "MemTotal:")
                totalMemory = value;
            else if (key == "MemFree:")
                freeMemory = value;
            else if (key == "Buffers:")
                buffers = value;
            else if (key == "Cached:")
                cached = value;
        }
    }

    long long usedMemory = totalMemory - freeMemory - buffers - cached;
    float memoryUsagePercent = (static_cast<float>(usedMemory) / totalMemory) * 100.0;

    return memoryUsagePercent;
}

float SystemStatusPrivate::getSysTotalMem()
{
    std::ifstream file("/proc/meminfo");
    std::string line;

    unsigned long totalMemory = 0;

    while (std::getline(file, line)) {
        if(line.compare(0, 9, "MemTotal:") == 0) {
            totalMemory = std::stoul(line.substr(10));
            return totalMemory / 1024.0;
        }
    }

    return 0;
}

qint32 SystemStatusPrivate::getCurProcessMemUsed()
{
    QFileInfo fileInfo("/proc/self/statm");
    if (!fileInfo.exists())
        return 0;

    QFile file(fileInfo.filePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList fields = line.split(' ', EeoSplitBehavior::SkipEmptyParts);
    if (fields.size() >= 2) {
        bool ok;
        long pageSize = sysconf(_SC_PAGESIZE);
        quint64 residentPages = fields[1].toULongLong(&ok);
        if (!ok)
            return 0;
        return residentPages * static_cast<quint64>(pageSize) / (1024*1024);
    }

    return 0;
}

QPair<float, float> SystemStatusPrivate::getCpuUsePercentage()
{
    return { getSysCpuUsePercentage(), get_proc_cpu(m_appId) };
}

float SystemStatusPrivate::getSysCpuUsePercentage()
{
    CPU_OCCUPY cpu_stat1;
    CPU_OCCUPY cpu_stat2;

    //获取内存
    //(MemTotal - MemFree)/ MemTotal
    //第一次获取cpu使用情况
    get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);

    usleep(100000);

    //第二次获取cpu使用情况
    get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);
    //计算cpu使用率
    return cal_cpuoccupy((CPU_OCCUPY *)&cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);
}
