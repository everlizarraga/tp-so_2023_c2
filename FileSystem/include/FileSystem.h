#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "m_gestor.h"
#include "fs_memoria.h"
#include "fs_kernel.h"

#define IP_FILESYSTEM "127.0.0.1"


t_log* filesystem_logger;
t_log* filesystem_log_obligatorio;
t_config* filesystem_config;

int server_fd_filesystem;
int fd_memoria;
int fd_kernel;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PUERTO_ESCUCHA;
char* PATH_FAT;
char* PATH_BLOQUES;
char* PATH_FCB;
int CANT_BLOQUES_TOTAL;
int CANT_BLOQUES_SWAP;
int TAM_BLOQUE;
int RETARDO_ACCESO_BLOQUE;
int RETARDO_ACCESO_FAT;



t_list* tabla_fat;
t_list* lista_bloques;

int tamanio_particion_swap;
int tamanio_particion_bloques;
int tamanio_fat;
t_list* lista_struct_fcbs;
t_list* lista_configs_fcbs;

void* buffer_swap;
uint32_t* buffer_bloques;
uint32_t* buffer_tabla_fat;

void leer_config(t_config* config);
void iterator(char* value);

void inicializar_archivos();
void inicializar_fcbs();
void destruir_fcb(t_fcb* fcb);
void destruir_archivo_fcb(t_archivo_fcb* archivo_fcb);
void destruir_listas_fcbs();
void crear_archivo_de_bloques();
void crear_fat();
void finalizar_filesystem();

void atender_filesystem_kernel(void);
void atender_memoria(void);
void atender_mensajes_kernel(t_buffer* buffer);

void ejecutar_f_open(char* nombre_archivo);
void ejecutar_f_create(char* nombre_archivo);
void ejecutar_f_truncate(char* nombre_archivo, int tamanio_nuevo);
void ejecutar_f_read(char* nombre_archivo, int dir_fisica, int posicion_a_leer, int pid);
void ejecutar_f_write(char* nombre_archivo, int dir_fisica, int posicion_a_escribir, int pid);
void asignar_bloques(int cant_bloques, t_archivo_fcb* fcb);
void sacar_bloques(int cant_bloques, t_archivo_fcb* fcb);
t_list* obtener_bloques_de_archivo(uint32_t bloque_actual, t_archivo_fcb* fcb);
t_bloque_fat* ultimo_bloque_archivo(uint32_t bloque_inicial, t_archivo_fcb* fcb);
t_archivo_fcb* buscar_fcb(char* nombre_archivo);
t_archivo_fcb* obtener_archivo(char* nombre_archivo);
void asignar_bloque_primer_truncate(t_archivo_fcb* fcb);
t_bloque_fat* buscar_bloque_libre();

void actualizar_archivo_fat(t_list* tabla_fat);

#endif /* FILESYSTEM_H_ */
