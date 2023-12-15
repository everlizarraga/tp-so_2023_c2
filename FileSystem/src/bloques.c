#include "../include/bloques.h"

//========== BLOQUES =====================

void* obtener_bloque(char* nombre_archivo, int nro_bloque){
    //LA info de nombre de archivo y puntero_de_kernel son para el log obligatorio
    //Acceso Bloque - Archivo: <NOMBRE_ARCHIVO> - Bloque Archivo: <NUMERO_BLOQUE_ARCHIVO> - Bloque FS: <NUMERO_BLOQUE_FS>
	log_warning(filesystem_logger, "inicio obtener_bloque");
    //LOG Obligatorio para acceso a SWAP
    //Acceso SWAP: <NRO_BLOQUE>

	void* bloque_a_obtener = malloc(TAM_BLOQUE);

	if(nombre_archivo == NULL){
		//Para obtener bloque SWAP
		memcpy(bloque_a_obtener, bloquesEnMemoria + nro_bloque, TAM_BLOQUE);
		log_info(filesystem_log_obligatorio, "Acceso SWAP: <%d>", nro_bloque);
		usleep(RETARDO_ACCESO_BLOQUE*1000);
	}else{
		//Para obtener bloque de archivo
		memcpy(bloque_a_obtener, bloquesEnMemoria + CANT_BLOQUES_SWAP + nro_bloque, TAM_BLOQUE);
		int nro_bloque_fs = nro_bloque + CANT_BLOQUES_SWAP + 1;
		log_info(filesystem_log_obligatorio, "Acceso Bloque - Archivo: <%s> - Bloque Archivo: <%d> - Bloque FS: <%d>", nombre_archivo, nro_bloque, nro_bloque_fs);
		usleep(RETARDO_ACCESO_BLOQUE*1000);
	}
	log_warning(filesystem_logger, "fin obtener_bloque");
	return bloque_a_obtener;
}

void modificar_bloque(char* nombre_archivo, int nro_bloque, void* contenido_bloque){
    //LA info de nombre de archivo y puntero_de_kernel son para el log obligatorio
    //Acceso Bloque - Archivo: <NOMBRE_ARCHIVO> - Bloque Archivo: <NUMERO_BLOQUE_ARCHIVO> - Bloque FS: <NUMERO_BLOQUE_FS>
	log_warning(filesystem_logger, "inicio modificar_bloque");
    //LOG Obligatorio para acceso a SWAP
    //Acceso SWAP: <NRO_BLOQUE>

	if(nombre_archivo == NULL){
		//Para obtener bloque SWAP
		memcpy(bloquesEnMemoria + nro_bloque, contenido_bloque, TAM_BLOQUE);
		log_info(filesystem_log_obligatorio, "Acceso SWAP: <%d>", nro_bloque);
		usleep(RETARDO_ACCESO_BLOQUE*1000);
	}else{
		//Para obtener bloque de archivo
		memcpy(bloquesEnMemoria + CANT_BLOQUES_SWAP + nro_bloque, contenido_bloque, TAM_BLOQUE);
		int nro_bloque_fs = nro_bloque + CANT_BLOQUES_SWAP + 1;
		log_info(filesystem_log_obligatorio, "Acceso Bloque - Archivo: <%s> - Bloque Archivo: <%d> - Bloque FS: <%d>", nombre_archivo, nro_bloque, nro_bloque_fs);
		usleep(RETARDO_ACCESO_BLOQUE*1000);
	}
	log_warning(filesystem_logger, "fin modificar_bloque");
}

//========== SWAP =====================

t_list* swap_obtener_n_cantidad_de_bloques(int cant_bloques){
	t_list* bloques_a_obtener = list_create();

	int contador = 0;

	log_warning(filesystem_logger, "inicio swap_obtener_n_cantidad_de_bloques: %d", bitarray_test_bit(bitmapSWAP, 2));

	for (int i = 0; i < bitarray_get_max_bit(bitmapSWAP); i++) {
		log_info(filesystem_logger, "VALOR BITMAP: %d en la pos de i: %d", bitarray_test_bit(bitmapSWAP, i), i);
		if (!bitarray_test_bit(bitmapSWAP, i)) {
			log_info(filesystem_logger, "AAA 3");
			int* ptr_contador = malloc(sizeof(int));
			*ptr_contador = i;
			list_add(bloques_a_obtener, ptr_contador);
			log_info(filesystem_logger, "AAA 4");
			contador++;
			if (contador == cant_bloques) {
				break;
			}
		} else {
			log_info(filesystem_logger, "AAA 5");
			contador = 0;
			list_clean(bloques_a_obtener);
			log_info(filesystem_logger, "AAA 6");
		}
	}
	log_info(filesystem_logger, "AAA 7");
	for(int i=0; i < list_size(bloques_a_obtener); i++){
		//si sale mal, asignar el list_get a un int
		bitarray_set_bit(bitmapSWAP, *((int*)list_get(bloques_a_obtener, i)));
		log_info(filesystem_log_obligatorio, "Acceso SWAP: <%d>", *((int*)list_get(bloques_a_obtener, i)));
		usleep(RETARDO_ACCESO_BLOQUE*1000);
	}

	log_warning(filesystem_logger, "fin swap_obtener_n_cantidad_de_bloques");
	return bloques_a_obtener;
}

void setear_bloque_de_swap_como_libre(uint32_t nro_bloque_swap){
    //LOG Obligatorio
    //Acceso SWAP: <NRO_BLOQUE>
	log_warning(filesystem_logger, "inicio setear_bloque_de_swap_como_libre");

	bitarray_clean_bit(bitmapSWAP, nro_bloque_swap);
	log_warning(filesystem_logger, "NUM BLOQUE SWAP: %d", nro_bloque_swap);
	memcpy(bloquesEnMemoria + nro_bloque_swap, "\0", TAM_BLOQUE);
	//memset(bloquesEnMemoria + nro_bloque_swap, 0, TAM_BLOQUE);
	log_info(filesystem_log_obligatorio, "Acceso SWAP: <%d>", nro_bloque_swap);
	usleep(RETARDO_ACCESO_BLOQUE*1000);


	log_warning(filesystem_logger, "fin setear_bloque_de_swap_como_libre");
}

