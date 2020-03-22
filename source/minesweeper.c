#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Valores constantes durante todo el juego
#define COLUMNS 30							// Número de columns del tablero
#define ROWS 20								// Número de filas del tablero
#define MINES 75							// Número de minas del tablero
#define SQUARE_SIZE 30						// Tamaño de las casillas en píxeles
#define SCREEN_WIDTH SQUARE_SIZE * COLUMNS	// Anchura de la ventana en píxeles
#define SCREEN_HEIGHT SQUARE_SIZE * ROWS	// Altura de la ventana en píxeles


// Ventana sobre la que renderizaremos
SDL_Window* window = NULL;

// Superficie de la ventana
SDL_Surface* window_surface = NULL;

// Superficies para cada una de las imágenes que cargaremos
SDL_Surface* covered = NULL;
SDL_Surface* covered_flagged = NULL;
SDL_Surface* covered_mine = NULL;
SDL_Surface* uncovered_0 = NULL;
SDL_Surface* uncovered_1 = NULL;
SDL_Surface* uncovered_2 = NULL;
SDL_Surface* uncovered_3 = NULL;
SDL_Surface* uncovered_4 = NULL;
SDL_Surface* uncovered_5 = NULL;
SDL_Surface* uncovered_6 = NULL;
SDL_Surface* uncovered_7 = NULL;
SDL_Surface* uncovered_8 = NULL;
SDL_Surface* uncovered_exploded = NULL;
SDL_Surface* you_win = NULL;
SDL_Surface* you_lose = NULL;

// Eventos de SDL
SDL_Event events;


// Inicializa SDL y crea la ventana
void initializeSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError());
	} else {
		window = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			printf("%s\n", SDL_GetError());
		} else {
			window_surface = SDL_GetWindowSurface(window);
		}
	}
}


// Carga la imagen de la ruta especificada y optimiza la superficie para que los posteriores blits sean más rápidos
SDL_Surface* loadSurface(char file[]) {
	SDL_Surface* loaded_surface = SDL_LoadBMP(file);
	SDL_Surface* optimized_surface = NULL;

	if (loaded_surface == NULL) {
		printf("%s\n", SDL_GetError());
	} else {
		optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, 0);

		if (optimized_surface == NULL) {
			printf("%s\n", SDL_GetError());
		}

		// Se libera la superficie sin optimizar ya que no la volveremos a necesitar
		SDL_FreeSurface(loaded_surface);
	}

	return optimized_surface;
}


// Carga todas las imágenes necesarias para el juego
void loadImages() {
	covered = loadSurface("images/covered.bmp");
	covered_flagged = loadSurface("images/covered_flagged.bmp");
	covered_mine = loadSurface("images/covered_mine.bmp");
	uncovered_0 = loadSurface("images/uncovered_0.bmp");
	uncovered_1 = loadSurface("images/uncovered_1.bmp");
	uncovered_2 = loadSurface("images/uncovered_2.bmp");
	uncovered_3 = loadSurface("images/uncovered_3.bmp");
	uncovered_4 = loadSurface("images/uncovered_4.bmp");
	uncovered_5 = loadSurface("images/uncovered_5.bmp");
	uncovered_6 = loadSurface("images/uncovered_6.bmp");
	uncovered_7 = loadSurface("images/uncovered_7.bmp");
	uncovered_8 = loadSurface("images/uncovered_8.bmp");
	uncovered_exploded = loadSurface("images/uncovered_exploded.bmp");
	you_win = loadSurface("images/you_win.bmp");
	you_lose = loadSurface("images/you_lose.bmp");
}


// Libera todas las imágenes cargadas anteriormente y finaliza SDL
void finalizeSDL() {
	// Libera todas las superficies excepto la superficie_ventana
	SDL_FreeSurface(covered);
	covered = NULL;

	SDL_FreeSurface(covered_flagged);
	covered_flagged = NULL;

	SDL_FreeSurface(uncovered_0);
	uncovered_0 = NULL;

	SDL_FreeSurface(uncovered_1);
	uncovered_1 = NULL;

	SDL_FreeSurface(uncovered_2);
	uncovered_2 = NULL;

	SDL_FreeSurface(uncovered_3);
	uncovered_3 = NULL;

	SDL_FreeSurface(uncovered_4);
	uncovered_4 = NULL;

	SDL_FreeSurface(uncovered_5);
	uncovered_5 = NULL;

	SDL_FreeSurface(uncovered_6);
	uncovered_6 = NULL;

	SDL_FreeSurface(uncovered_7);
	uncovered_7 = NULL;

	SDL_FreeSurface(uncovered_8);
	uncovered_8 = NULL;

	SDL_FreeSurface(covered_mine);
	covered_mine = NULL;

	SDL_FreeSurface(you_win);
	you_win = NULL;

	SDL_FreeSurface(you_lose);
	you_lose = NULL;

	// Libera la ventana, tambien se encarga de liberar la superficie superficie_ventana
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}


// Inicializa los dos tableros, rellenando el tablero oculto de casillas vacías '0' y el tablero del jugador de casillas tapadas '-'
void initializeBoards(char hidden_board[ROWS][COLUMNS], char player_board[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			hidden_board[i][j] = '0';
			player_board[i][j] = '-';
		}
	}
}


// Muestra en pantalla el tablero del jugador
void drawBoard(char player_board[ROWS][COLUMNS]) {
	SDL_Rect square;	// Posición de la superficie en la que se dibujará la casilla

	square.x = 0;
	square.y = 0;
	square.w = SQUARE_SIZE;
	square.h = SQUARE_SIZE;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			square.x = j * SQUARE_SIZE;
			square.y = i * SQUARE_SIZE;

			switch (player_board[i][j]) {
				case '-':
					SDL_BlitSurface(covered, NULL, window_surface, &square);
					break;
				case 'F':
					SDL_BlitSurface(covered_flagged, NULL, window_surface, &square);
					break;
				case 'M':
					SDL_BlitSurface(covered_mine, NULL, window_surface, &square);
					break;
				case '0':
					SDL_BlitSurface(uncovered_0, NULL, window_surface, &square);
					break;
				case '1':
					SDL_BlitSurface(uncovered_1, NULL, window_surface, &square);
					break;
				case '2':
					SDL_BlitSurface(uncovered_2, NULL, window_surface, &square);
					break;
				case '3':
					SDL_BlitSurface(uncovered_3, NULL, window_surface, &square);
					break;
				case '4':
					SDL_BlitSurface(uncovered_4, NULL, window_surface, &square);
					break;
				case '5':
					SDL_BlitSurface(uncovered_5, NULL, window_surface, &square);
					break;
				case '6':
					SDL_BlitSurface(uncovered_6, NULL, window_surface, &square);
					break;
				case '7':
					SDL_BlitSurface(uncovered_7, NULL, window_surface, &square);
					break;
				case '8':
					SDL_BlitSurface(uncovered_8, NULL, window_surface, &square);
					break;
				case 'E':
					SDL_BlitSurface(uncovered_exploded, NULL, window_surface, &square);
					break;
				default:
					break;
			}
		}
	}

	SDL_UpdateWindowSurface(window);
}


// Procesa los eventos que hay en cola para comprobar si se ha pulsado la X de la ventana o si se ha pulsado un botón del ratón
void processEvents(bool* quit, bool* mouse_left_pressed, bool* mouse_right_pressed, int* mouse_x, int* mouse_y) {
	// Mientras no se hayan procesado todos los eventos en cola
	while (SDL_PollEvent(&events) != 0) {
		if (events.type == SDL_QUIT) {
			*quit = true;	// Se ha pulsado la X de la ventana para salir del juego
		} else if (events.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(mouse_x, mouse_y);	// Se guarda la posición del puntero tras haber pulsado un botón

			if (events.button.button == SDL_BUTTON_LEFT) {
				*mouse_left_pressed = true;		// Se ha pulsado el botón izquierdo del ratón
			} else if (events.button.button == SDL_BUTTON_RIGHT) {
				*mouse_right_pressed = true;	// Se ha pulsado el botón derecho del ratón
			}
		}
	}
}


// Coloca las minas 'M' en el tablero oculto repartiéndolas de forma aleatoria
void placeMines(int square_x, int square_y, char hidden_board[ROWS][COLUMNS]) {
	int mines_remaining = MINES;	// Numero de minas que faltan por colocar en el tablero
	int random_row;					// Fila de la casilla donde se coloca la mina
	int random_column;				// Columna de la casilla donde se coloca la mina

	do {
		// Se genera una fila y una column aleatorias que determinan una casilla aleatoria
		random_row = rand() % ROWS;
		random_column = rand() % COLUMNS;

		// Si en la casilla no se había puesto ya antes una mina, ni es la primera casilla que ha destapado el jugador (square_x, square_y), entonces se coloca una mina 'M' en dicha casilla
		if (hidden_board[random_row][random_column] != 'M' && (random_row != square_y || random_column != square_x)) {
			hidden_board[random_row][random_column] = 'M';
			mines_remaining--;
		}
	} while (mines_remaining > 0);
}


// Devuelve el número de minas que hay alrededor de una casilla de coordenadas row, column
char countMines(char hidden_board[ROWS][COLUMNS], int row, int column) {
	char mines = 0;					// Numero de minas contadas alrededor de la casilla

	// Se establecen los límites entre los que se encuentran las minas alrededor de la casilla
	int max_row = row + 1; 			// Fila que hay debajo de la casilla
	int min_row = row - 1;			// Fila que hay encima de la casilla
	int min_column = column - 1;	// Columna a la izquierda de la casilla
	int max_column = column + 1;	// Columna a la derecha de la casilla

	// Si la casilla está en los bordes del tablero entonces se modifican los límites para no recorrer fuera del tablero
	if (row == 0) min_row = 0;
	else if (row == ROWS - 1) max_row = ROWS - 1;
	if (column == 0) min_column = 0;
	else if (column == COLUMNS - 1) max_column = COLUMNS - 1;

	// Se recorren todas las casillas que hay dentro de los límites contando las minas que hay en ellas
	for (int i = min_row; i <= max_row; i++) {
		for (int j = min_column; j <= max_column; j++) {
			if (hidden_board[i][j] == 'M') {
				mines++;
			}
		}
	}

	// Se devuelve el numero de minas que hay alrededor de la casilla
	return '0' + mines;
}


// En cada casilla del tablero en la que no haya una mina, coloca el número de minas que tiene a su alrededor
void placeNumbers(char hidden_board[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (hidden_board[i][j] !='M') {
				hidden_board[i][j] = countMines(hidden_board, i, j);
			}
		}
	}
}


// Destapa las casillas que sean necesarias tras pulsar una casilla y devuelve el número de casillas destapadas
int uncoverSquares(char hidden_board[ROWS][COLUMNS], char player_board[ROWS][COLUMNS], int row, int column) {
	if (player_board[row][column] == '-') {
		player_board[row][column] = hidden_board[row][column];	// Se destapa la casilla en el tablero del jugador, mostrando lo que estaba oculto en ella

		if (player_board[row][column] == '0') {
			// Número de casillas destapadas
			int uncovered_squares = 1;

			// Se establecen los límites entre los que se encuentran las minas alrededor de la casilla
			int max_row = row + 1; 			// Fila que hay debajo de la casilla
			int min_row = row - 1;			// Fila que hay encima de la casilla
			int min_column = column - 1;	// Columna a la izquierda de la casilla
			int max_column = column + 1;	// Columna a la derecha de la casilla

			// Si la casilla está en los bordes del tablero entonces se modifican los límites para no recorrer fuera del tablero
			if (row == 0) min_row = 0;
			else if (row == ROWS - 1) max_row = ROWS - 1;
			if (column == 0) min_column = 0;
			else if (column == COLUMNS - 1) max_column = COLUMNS - 1;

			// Se recorren todas las casillas que hay dentro de los límites aplicando de forma recursiva la función a cada una de ellas
			for (int i = min_row; i <= max_row; i++) {
				for (int j = min_column; j <= max_column; j++) {
					if (i != row || j != column) {
						uncovered_squares += uncoverSquares(hidden_board, player_board, i, j);
					}
				}
			}

			return uncovered_squares;	// Si la casilla era '0', se ha destapado más de una casilla
		} else {
			return 1;	// Si la casilla no era '0', solo se destapa esa casilla
		}
	} else {
		return 0;	// Si la casilla ya estaba destapada, no se destapa ninguna casilla
	}
}


// Comprueba qué tipo de casilla y con qué botón ha sido pulsada y actúa en consecuencia
void playGame(int* covered_squares, bool* game_over, bool mouse_right_pressed, bool mouse_left_pressed, int square_y, int square_x, char player_board[ROWS][COLUMNS], char hidden_board[ROWS][COLUMNS]) {
	// Si se ha pulsado el botón derecho del ratón
	if (mouse_right_pressed == true) {
		if (player_board[square_y][square_x] == '-') {
			player_board[square_y][square_x] = 'F';
		} else if (player_board[square_y][square_x] == 'F') {
			player_board[square_y][square_x] = '-';
		}
	}

	// Si se ha pulsado el botón izquierdo del ratón
	if (mouse_left_pressed == true) {
			if (player_board[square_y][square_x] == '-' && hidden_board[square_y][square_x] == 'M') {
				player_board[square_y][square_x] = 'E';
				*game_over = true;	// Se pierde la partida si la casilla pulsada era una mina
		} else {
			*covered_squares -= uncoverSquares(hidden_board, player_board, square_y, square_x);
		}
	}

	// Si has perdido se destapan el resto de minas ocultas
	if (*game_over == true) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLUMNS; j++) {
				if (player_board[i][j] != 'E' && hidden_board[i][j] == 'M') {
					player_board[i][j] = 'M';
				}
			}
		}
	}
}


int main(int argc, char* args[]) {
	bool mouse_left_pressed = true;
	bool mouse_right_pressed = true;
	bool game_over = false;
	bool quit = false;

	char hidden_board[ROWS][COLUMNS];		// Tablero oculto en el que estaran almacenadas las posiciones de las minas
	char player_board[ROWS][COLUMNS];		// Tablero que se muestra al jugador en pantalla

	int mouse_x, mouse_y;		// Posición del puntero en píxeles
	int square_x, square_y;		// Posición del puntero en casillas
	int covered_squares;		// Número de casillas tapadas

	// Posibles estados en los que se puede encontrar el juego
	enum { INITIALIZING_BOARDS, PLACING_MINES, PLAYING_GAME, ENDING_GAME } game_state = INITIALIZING_BOARDS;

	// Posición de la superficie donde se dibujará el mensaje de has ganado o has perdido
	SDL_Rect message;
		message.x = SCREEN_WIDTH / 2 - 540 / 2;
		message.y = SCREEN_HEIGHT / 2 - 120 / 2;
		message.w = 540;
		message.h = 120;

	srand(time(0));

	initializeSDL();

	loadImages();

	SDL_SetWindowIcon(window, uncovered_exploded);

	// Game loop
	while (!quit) {

		processEvents(&quit, &mouse_left_pressed, &mouse_right_pressed, &mouse_x, &mouse_y);
		square_x = mouse_x / SQUARE_SIZE;
		square_y = mouse_y / SQUARE_SIZE;

		if (mouse_left_pressed == true || mouse_right_pressed == true) {

			switch (game_state) {

				case INITIALIZING_BOARDS:
					initializeBoards(hidden_board, player_board);
					drawBoard(player_board);
					covered_squares = COLUMNS * ROWS;
					game_state = PLACING_MINES;
					break;

				case PLACING_MINES:
					placeMines(square_x, square_y, hidden_board);
					placeNumbers(hidden_board);
					covered_squares -= uncoverSquares(hidden_board, player_board, square_y, square_x);
					drawBoard(player_board);
					game_state = PLAYING_GAME;
					break;

				case PLAYING_GAME:
					if (covered_squares > MINES && game_over == false) {
						playGame(&covered_squares, &game_over, mouse_right_pressed, mouse_left_pressed, square_y, square_x, player_board, hidden_board);
						drawBoard(player_board);
					}
					if (covered_squares == MINES || game_over == true) {
						game_state = ENDING_GAME;
					}
					break;

				case ENDING_GAME:
					if (game_over == true) {
						SDL_BlitSurface(you_lose, NULL, window_surface, &message);
						game_over = false;
					} else {
						SDL_BlitSurface(you_win, NULL, window_surface, &message);
					}
					SDL_UpdateWindowSurface(window);
					game_state = INITIALIZING_BOARDS;
					break;
			}

			mouse_left_pressed = false;
			mouse_right_pressed = false;
		}

		SDL_Delay(33);
	}

	finalizeSDL();

	return 0;
}
