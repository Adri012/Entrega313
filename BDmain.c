//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int puntuacion;
	char demanda[30];
	char consulta [200];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos de la base de datos
	err=mysql_query (conn, "SELECT * FROM Jugador");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta. El resultado de la consulta se devuelve en una variable del tipo puntero a MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria en la que cada fila contiene los datos de una persona.
	
	// Ahora obtenemos la primera fila que se almacena en una variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	// En una fila hay tantas columnas como datos tiene una persona. En nuestro caso hay tres columnas: dni(row[0]), nombre(row[1]) y edad (row[2]).
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf("Nombres de los Jugadores: \n");
		while (row !=NULL) {
			// las columnas 1 y 3 contienen nombre y partidas ganadas 
			printf ("%s \n", row[1]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
		
		
		
		// Ahora vamos a buscar la puntuación de la persona que el usuario introduzca
		printf ("\nDame el Nombre de quien quieras conocer la puntuacion: \n"); 
		scanf ("%s", demanda);
		// construimos la consulta SQL
		strcpy (consulta,"SELECT Count(Jugador.usuario) FROM (Jugador, Partida) WHERE Jugador.id=Partida.ganador_id AND Jugador.usuario='"); 
		strcat (consulta, demanda);
		strcat (consulta,"'");
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else
			// El resultado debe ser una matriz con una sola fila y una columna que contiene el nombre
			puntuacion = atoi(row[0]);
			printf ("\nPartidas ganadas de %s: %d\n", demanda, puntuacion);
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
