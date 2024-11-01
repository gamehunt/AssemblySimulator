#ifndef AMD64ASSEMBLYPLUGIN_H
#define AMD64ASSEMBLYPLUGIN_H

#include <QGenericPlugin>

#include <libs/LibAssembly/assembly.h>

class AMD64AssemblyPlugin : public AssemblyInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid FILE "AMD64.json")
    Q_INTERFACES(AssemblyInterface)

public:
    explicit AMD64AssemblyPlugin();

    QString getName() override;
    Assembly* getAssembly() override;
};

#endif // AMD64ASSEMBLYPLUGIN_H
