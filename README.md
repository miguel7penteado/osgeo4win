# OSGEO4W

[![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/miguel-penteado-760486a9/)
&nbsp;
[![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/miguel7penteado)

## 1-Instalar dependências

Baixe e instale o pacote cygwin para que você tenha as seguintes 
dependências disponíveis:

Dependências de Compilação - GNU for windows
* autoconf
* automake
* libtool
* bison
* flex
* mingw-gcc-g++
* make
* libiconv
* libbz2-devel 

Mingw - Bibliotecas GNU for windows
* mingw-zlib
* mingw-bzip2 

Utilidades
* upx 

```bash
http://www.cygwin.com/setup.exe
```

## 2-Como compilar o pacote de ferramentas geográficas OSGEO4W

```bash
#Obtendo o pacote
svn co https://svn.osgeo.org/osgeo4w/trunk/setup
```

## 3-Compilando o pacote e criando o instalador

```bash
cd setup

# recriar o arquivo de configuração
# Se você quiser ativar um site espelho, você deve adicionar a opção --enable-mirror option (detalhes no README)
./bootstrap.sh  

# aqui deve ser produzido o osgeo4w-setup-x86.exe no diretório de setup.
make 

# Limpe se achar necessário
make clean
```
