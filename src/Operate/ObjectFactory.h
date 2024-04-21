#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "GameObject.h"
#include<bits/stdc++.h>
using namespace std;
class ObjectFactory
{
    public:
        GameObject* CreateObject(string type, Properties* props);
        void RegisterType(string className, function<GameObject*(Properties*props)> type);

        static ObjectFactory* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory();
        }

    private:
        ObjectFactory() {}
        static ObjectFactory* s_Instance;
        map<string,function<GameObject*(Properties*props)>> m_TypeRegistry;
};

template<class Type>
class Register
{
    public:
        Register(string className)
        {
            ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {
                return new Type(props);
            });
        }
};

#endif
