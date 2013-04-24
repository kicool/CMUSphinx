#
## 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#
# # define the C compiler to use
# CC = gcc
#
# # define any compile-time flags
# CFLAGS = -Wall -g
#
# # define any directories containing header files other than /usr/include
# #
INCLUDE = -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx

LFLAGS = -lpocketsphinx -lsphinxbase

ps:
	gcc $(INCLUDE) $(LFLAGS) -o ps ps.c
