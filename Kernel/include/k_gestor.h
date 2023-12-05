#ifndef K_GESTOR_H_
#define K_GESTOR_H_

#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/string.h>
#include <pthread.h>
#include <semaphore.h>

#include <protocolo.h>
#include <shared.h>
#include <socket.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef enum{
	FIFO,
	ROUNDROBIN,
	PRIORIDADES
}t_algoritmo;

typedef enum{
	NEW,//=0
	READY,//=1
	EXEC,//=2
	BLOCKED,//=3
	EXIT//=4
}est_pcb;

typedef struct{
	uint32_t AX;
	uint32_t BX;
	uint32_t CX;
	uint32_t DX;
}t_registros_CPU;

// Hay que agregar dos enum, uno que sea motivo_bloqueo y otro motivo_finalizacion.
typedef struct{
	int pid;
	int ticket;
	int program_counter;
	int prioridad;
	int size;
	char* path;
	est_pcb estado;
	char* motivo_vuelta;
	t_registros_CPU* registros_CPU;
	t_list* lista_recursos_pcb;
	pthread_mutex_t mutex_lista_recursos;  // --> No se si es necesaria
	void* tabla_de_archivos_abiertos;
}t_pcb;

typedef struct{
	char* recurso_name;
	int instancias;
	t_list* lista_bloqueados;
	t_list* lista_asignados;
	pthread_mutex_t mutex_bloqueados;
	pthread_mutex_t mutex_asignados;
}t_recurso;

typedef struct{
	t_pcb* pcb_a_sleep;
	int tiempo_en_block;
}t_sleep;


extern t_log* kernel_logger;
extern t_log* kernel_log_obligatorio;
extern t_config* kernel_config;

extern pthread_t hilo_cpu_dispatch;
extern pthread_t hilo_cpu_interrupt;
extern pthread_t hilo_memoria;
extern pthread_t hilo_consola;
extern pthread_t hilo_filesystem;

extern int fd_filesystem;
extern int fd_cpu_dispatcher;
extern int fd_cpu_interrupt;
extern int fd_memoria;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_FILESYSTEM;
extern char* PUERTO_FILESYSTEM;
extern char* IP_CPU;
extern char* PUERTO_CPU_DISPATCH;
extern char* PUERTO_CPU_INTERRUPT;
extern t_algoritmo ALGORITMO_PLANIFICACION;
extern int QUANTUM;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;
extern int GRADO_MULTIPROGRAMACION_INI;

extern int process_id;
extern int procesos_en_core;
extern int var_pausa;
extern int var_ticket;
// Para determinar en el hilo de interrupt si se finaliza proceso por DESALOJO PRO CONSOLA
extern int flag_finalizar_proceso;


// ------ Listas ------
extern t_list* lista_new;
extern t_list* lista_ready;
extern t_list* lista_execute;
extern t_list* lista_blocked;
extern t_list* lista_blocked_fs;
extern t_list* lista_exit;

extern t_list* lista_instructions;
extern t_list* lista_general;
extern t_list* lista_recursos;


//Para controlar la habilitacion de interrupciones - Algo. Prioridad
extern bool interrupcion_habilitada;

//Estado de CPU
extern bool CPU_en_uso;

//Para dar prioridad a la interrupcion por consola sobre la de quantum
extern bool flag_exit;

//--Van juntos para controlar PIORIDADES
extern bool hay_pcb_elegida;
extern t_pcb* pcb_prioritaria;


// ------ SEMAFOROS ------
extern sem_t sem_pausa;
extern sem_t sem_enviar_interrupcion;
extern sem_t sem_estructura_iniciada;


// ------ PTHREAD_MUTEX ------
extern pthread_mutex_t mutex_lista_new;
extern pthread_mutex_t mutex_lista_ready;
extern pthread_mutex_t mutex_lista_exec;
extern pthread_mutex_t mutex_lista_blocked;
extern pthread_mutex_t mutex_lista_exit;
extern pthread_mutex_t mutex_lista_general;

extern pthread_mutex_t mutex_process_id;
extern pthread_mutex_t mutex_core;
extern pthread_mutex_t mutex_pausa;
extern pthread_mutex_t mutex_recurso;
extern pthread_mutex_t mutex_ticket;
extern pthread_mutex_t mutex_enviar_interrupcion;

extern pthread_mutex_t mutex_flag_exit;
extern pthread_mutex_t mutex_flag_finalizar_proceso;

void public_imprimir_procesos_por_estado_v0();
void public_imprimir_procesos_por_estado_v1();

#endif /* K_GESTOR_H_ */
