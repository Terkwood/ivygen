/**************************************************************************************
**
**  Copyright (C) 2006 Thomas Luft, University of Konstanz. All rights reserved.
**
**  This file is part of the Ivy Generator Tool.
**
**  This program is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the
**  Free Software Foundation; either version 2 of the License, or (at your
**  option) any later version.
**  This program is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
**  for more details.
**  You should have received a copy of the GNU General Public License along
**  with this program; if not, write to the Free Software Foundation,
**  Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA 
**
***************************************************************************************/


#include "model_loader.h"
#include "basic_mesh.h"

#include <QMessageBox>
#include <QDir>
#include <QFileInfo>

QHash<QString, ImporterInterface*> *ModelLoader::importersMap = nullptr;
QHash<QString, ExporterInterface*> *ModelLoader::exportersMap = nullptr;

bool ModelLoader::load( const std::string &path, const std::string &file, BasicMesh &model  )
{
    QFile qfile(file.c_str());
    QFileInfo info(qfile);

    QString extension = info.completeSuffix();
    ImporterInterface* importer = importersMap->value(extension, nullptr);

    if(!importer)
        return false;

    return importer->load(path, file, model);
}

bool ModelLoader::save(const std::string &path, const std::string &file, BasicMesh &model)
{
    QFile qfile(file.c_str());
    QFileInfo info(qfile);

    QString extension = info.completeSuffix();
    ExporterInterface* exporter = exportersMap->value(extension, nullptr);

    if(!exporter)
        return false;

    return exporter->save(path, file, model);
}

void ModelLoader::initializeImporters(QList<ImporterInterface*> *importers)
{
    importersMap = new QHash<QString, ImporterInterface*>();
    for(ImporterInterface* importer : *importers)
    {
        QString extension = importer->getFileExtension();
        importersMap->insert(extension, importer);
    }
}

void ModelLoader::initializeExporters(QList<ExporterInterface*> *exporters)
{
    exportersMap = new QHash<QString, ExporterInterface*>();
    for(ExporterInterface* exporter : *exporters)
    {
        QString extension = exporter->getFileExtension();
        exportersMap->insert(extension, exporter);
    }
}
