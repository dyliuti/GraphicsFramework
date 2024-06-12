#pragma once

#define DECLARE_SHARE(ClassName) \
private: \
    static ClassName *m_spInstance; \
\
public: \
    static ClassName *instance() \
    { \
        if (NULL == m_spInstance) { \
            m_spInstance = new ClassName(); \
            static Cleaner s_clean; \
        } \
        return m_spInstance; \
    } \
\
private: \
    class Cleaner \
    { \
    public: \
        Cleaner() {} \
        ~Cleaner() \
        { \
            if (ClassName::instance()) \
                delete ClassName::instance(); \
        } \
    };

#define BUILD_SHARE(ClassName) ClassName *ClassName::m_spInstance = NULL;
