#include "profesoraux.h"

bool compruebaRol(Profesor usuarioAux){
    ifstream file("iniciosesion.bin", ios::in | ios::binary);
    bool correcto = false;
    string auxiliar;
    RegUsu aux;
    if(file.is_open()){
        while(!file.eof()){
            file.read((char*) &aux, sizeof(RegUsu));
            if(aux.usuario == usuarioAux.getUsuario()){
                auxiliar=aux.rol;
                if(auxiliar == "Ayudante"){
                    correcto = true;
                }
            }else{
                correcto=false;
            }
        }
        file.close();
    }
    return correcto;
}
