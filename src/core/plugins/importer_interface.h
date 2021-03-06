#ifndef IMPORTERINTERFACE_H
#define IMPORTERINTERFACE_H

#include <core/basic_mesh.h>

#include <QtPlugin>

#define ImporterInterface_iid "com.ivygen.importerplugin"

class ImporterInterface
{
public:
    virtual ~ImporterInterface() {}

    virtual bool load( const std::string &path, const std::string &file, BasicMesh &model  ) = 0;

    virtual QString getName() = 0;

    virtual QString getFileExtension() = 0;
};

Q_DECLARE_INTERFACE(ImporterInterface, ImporterInterface_iid)

#endif // IMPORTERPLUGIN_H
