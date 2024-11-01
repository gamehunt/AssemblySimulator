#include "amd64assemblyplugin.h"

#include "amd64assembly.h"

AMD64AssemblyPlugin::AMD64AssemblyPlugin()
{}

QString AMD64AssemblyPlugin::getName() {
    return "x86-64 NASM";
}

Assembly* AMD64AssemblyPlugin::getAssembly() {
    return new AMD64Assembly();
}
