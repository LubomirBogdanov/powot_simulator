/*
    Copyright (C) 2016 Lubomir Bogdanov

    Contributor Lubomir Bogdanov <lubomirb@yahoo.com>

    This file is part of Powot Simulator.

    Powot Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Powot Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Powot Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "fileio.h"

fileio::fileio(){
    //error.display_error(CANT_OPEN_FILE, (const QString *)"String");
}

fileio::~fileio(){

}

/*!
  \brief Reads a file and stores its contents in the QStringList buffer. Returns one on success and zero if
  the opening of the file failed.

  \param filename - the name of the file to be opened.

  \param contents - a buffer containing all the lines in the file.
  */
bool fileio::read_entire_file(const QString *filename, QStringList *contents){
    bool err = 0;
    QString currentline;

    QFile file(*filename);
    err = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(err){
        err = 1;
        QTextStream FileStream(&file);
        while(!FileStream.atEnd()){
            //Do not use *Contents << FileStream.readLine(); because it will remove the newlines from the file.
            currentline = FileStream.readLine();
            *contents << currentline;
        }
        file.close();
    }
    else{
        error.display_error(CANT_OPEN_FILE, filename);
    }

    return err;
}

/*!
  \brief Same as read_entire_file( ) but excludes comments, denoted with '#'.

  \param filename - the name of the configuration file to be opened.

  \param contents - a buffer containing all the lines in the configuration file.
  */
bool fileio::read_entire_config_file(const QString *filename, QStringList *contents){
    bool err = 0;
    QString currentline;

    QFile file(*filename);
    err = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(err)
    {
        err = 1;
        QTextStream FileStream(&file);
        while(!FileStream.atEnd())
        {
            //Do not use *Contents << FileStream.readLine(); because it will remove the newlines from the file.
            currentline = FileStream.readLine();
            if(currentline.contains("#")) //Exclude comments
            {
                int ind = currentline.indexOf("#");
                ind = currentline.size() - ind;
                currentline.chop(ind);
            }

            *contents << currentline;

        }
        file.close();
    }
    else{
        error.display_error(CANT_OPEN_FILE, filename);
    }

    return err;
}

/*!
  \brief Writes the QStringList buffer to a file. Returns one on success and zero if
  the writing to the file failed.

  \param FileName - the name of the file to write to.

  \param Contents - a buffer containing all the lines to be written to the file.
  */
bool fileio::write_entire_file(QString *filename, QStringList *contents){
    bool err = 0;

    QFile file(*filename);
    err = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(err){
        err = 1;
        QTextStream FileStream(&file);
        for(qint32 i = 0; i < contents->size(); i++){
            FileStream << contents->at(i);
            FileStream << endl;
        }

        file.close();
    }
    else{
       error.display_error(CANT_WRITE_FILE, filename);
    }

    return err;
}
