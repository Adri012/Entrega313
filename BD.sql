DROP DATABASE IF EXISTS Juego;
CREATE DATABASE Juego;
USE Juego;

CREATE TABLE Jugador(
  id INTEGER AUTO_INCREMENT,
  usuario VARCHAR(30) NOT NULL,
  contrasena VARCHAR(80) NOT NULL,
  partidas_ganadas INT,
  PRIMARY KEY (id)
)ENGINE = InnoDB;
 
CREATE TABLE Partida (
  id INT NOT NULL,
  dia VARCHAR(12),
  hora VARCHAR(10),
  ganador_id INT,
  FOREIGN KEY (ganador_id) REFERENCES Jugador(id),
  PRIMARY KEY (id)
)ENGINE = InnoDB;


INSERT INTO Jugador(usuario, contrasena, partidas_ganadas) VALUES ("Chao",  "1111", 0);
INSERT INTO Jugador(usuario, contrasena, partidas_ganadas) VALUES ("David", "2222", 0);
INSERT INTO Jugador(usuario, contrasena, partidas_ganadas) VALUES ("Adria", "3333", 0);
INSERT INTO Jugador(usuario, contrasena, partidas_ganadas) VALUES ("Angel", "4444", 0);

INSERT INTO Partida VALUES (1, '17/03/2023','10:20', 1);
INSERT INTO Partida VALUES (2, '17/03/2023','12:42', 1);
INSERT INTO Partida VALUES (3, '17/03/2023','14:30', 3);
INSERT INTO Partida VALUES (4, '17/03/2023','16:16', 4);
INSERT INTO Partida VALUES (5, '18/03/2023','12:22', 3);
INSERT INTO Partida VALUES (6, '18/03/2023','18:47', 3);
INSERT INTO Partida VALUES (7, '18/03/2023','19:23', 4);
INSERT INTO Partida VALUES (8, '18/03/2023','20:12', 3);


SELECT Count(Jugador.usuario) FROM (Jugador, Partida) WHERE Jugador.id=Partida.ganador_id AND Jugador.usuario="Adria";


