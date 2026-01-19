	/*  NRC 15849   Proyecto etapa I.  Integrantes:
			Mendoza Juan       C.I.  31.951.748              López Elian   C.I.   31.867.990
			Contreras Joseph C.I. 31.573.231		Andrés González C.I. 31.745.166          */

#include <iostream>
#include <string.h>
using namespace std;

//Estructuras

struct listaventas {
	int fecha, cantidad;
	listaventas *prox;
};

struct listaprods {
	int codigo, existencia, min;
	listaprods *prox;
	listaventas *ventas;
};

struct producto {
	int codigo;
	char nombre [20], marca [20];
	producto *sig;
};

struct tienda {
	int codigo, telefono;
	char nombre [20], direccion [20];
	tienda *next;
	listaprods *prods;
};

//Procedimientos y funciones

void bufc () { //Limpia el buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int isnum (char num []) { //Comprobrar si una cadena de caracteres es un número
	for (size_t i = 0; i < strlen (num); i ++) if (!(isdigit(num [i]) || num [i] == '-')) return 0;
	return 1;
}

void tabscalc (char x []) { //Calcular cantidad de tabs ¿Qué se hacen al imprimir datos
	int tes = 3 - (strlen (x) / 8);
	for (int i = 0; i < tes; i ++) cout << "\t";
}

void printcentrado (char x []) {
	int spc = (168 - strlen (x)) / 2;
	for (int i = 0; i < spc; i++) cout << " ";
	cout << x;
}

int cinnum (int bucle = 1) {
	char num [10] = "";
	scanf ("%9[^\n\t]", num);
	bufc ();
	if (bucle && !isnum (num))
	while (!isnum (num) || num [0] == '\0') {
		cout << "Lo ingresado no es un número, intente nuevamente: ";
		scanf ("%9[^\n\t]", num);
		bufc ();
	}
	else if (!isnum (num)) {
		cout << "Lo ingresado no es un número.\n\n";
		return -1;
	}
	return atoi (num);
}

void encabezado () {
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"; 
	printcentrado ("S I S T E M A  I N V E N T A R I O");
	cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
}

void encabezadoinv (tienda *inv) {
	char x [40] = "Tienda: ";
	if (inv) {
		char y [10];
		itoa (inv -> codigo, y, 10);
		strcat (x, y);
		strcat (x, " ");
		strcat (x, inv -> nombre);
	}
	else strcat (x, "N/A");
	printcentrado (x);
	cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
}

int sino (char y[] = "¿Seguro de que desea realizar este cambio?") {
	cout << y << ":\n\n1. Sí\n0. No\n\nSu opción: ";
	int x = cinnum (0);
	return x;
}

//Procedimientos para producto

void cargararchivoproducto (FILE *file, producto **p) {
	if (file && !feof (file)) {
		*p = new producto;
		fscanf (file, "%d\t%19[^\n\t]\t%19[^\n\t]\n", &((*p) -> codigo), &((*p) -> nombre), &((*p) -> marca));
		if ((*p) -> codigo == -842150451) {delete *p; *p = NULL; fclose (file);}
		else cargararchivoproducto (file, &((*p) -> sig));
	}
	else {*p = NULL; if (file) fclose (file);}
}

void guardararchivoproducto (FILE *file, producto *p) {
	if (file && p) {
		fprintf (file, "%d\t%s\t%s", p -> codigo, p -> nombre, p -> marca);
		if (p -> sig) fprintf (file, "\n");
		guardararchivoproducto (file, p -> sig);
	}
	else if (!file) {cout << "Error guardando el archivo productos.txt.\n\n"; system ("pause");}
	else if (file) fclose (file);
}

producto *buscarcode (producto *p, int code) {
	while (p) {
		if (code == p -> codigo) return p;
		p = p -> sig;
	}
	return NULL;
}

void consultarcode (producto *p, int code, int encabezado = 1, int salto = 1) {
	if (p) {
		while (p && p -> codigo != code) p = p -> sig;
		if (p) {
			if (encabezado) cout << "\t\t\t\t\t\t\tCódigo\t\t\tNombre\t\t\tMarca\n" << "\t\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\t\t\t\t\t\t\t";
			cout << p -> codigo << "\t\t\t" << p -> nombre;
			tabscalc (p -> nombre);
			cout << p -> marca;
			if (encabezado && salto) cout << "\n\t\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
			else tabscalc (p -> marca);
		}
		else cout << "\nNo hay ningún producto con ese código.\n\n";
	}
	else cout << "\nNo hay productos para consultar.\n\n";
}

void consultarnombre (producto *p) {
	if (p) {
		producto *aux = p;
		char x [20];
		int encabezado = 1;
		cout << "Ingrese el nombre del producto ¿Qué desea consultar: ";
		scanf ("%19[^\n\t]", x);
		bufc ();
		while (aux) {
			if (!_strcmpi (aux -> nombre, x)) {
				if (encabezado) {cout << "\n\t\t\t\t\t\t\tCódigo\t\t\tNombre\t\t\tMarca\n" << "\t\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"; encabezado = 0;}
				cout << "\t\t\t\t\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
				tabscalc (aux -> nombre);
				cout << aux -> marca << "\n";
			}
			aux = aux -> sig;
		}
		if (encabezado) cout << "\nNo hay ningún producto con ese nombre.\n\n";
		else cout << "\t\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
	}
	else cout << "No hay productos para consultar.\n\n";
	system ("pause");
}

int cantidadventas (listaventas *p, int elim = 1) {
	int cant = 0;
	if (p) {
		cant += (p -> cantidad) + cantidadventas (p -> prox, elim);
		if (elim) delete p;
	}
	return cant;
}

int eliminarprodventa (listaprods **p, int code, int *ventas) {
	if (*p) 
		if ((*p) -> codigo == code) {
			listaprods *aux = (*p);
			*ventas += cantidadventas ((*p) -> ventas);
			int x = (*p) -> existencia;
			*p = aux -> prox;
			delete aux;
			return x;
		}
		else return eliminarprodventa (&((*p) -> prox), code, ventas);
	else return 0;
}

void eliminarprod (producto **p, tienda *t) {
	if (*p) {
		int code, x, total = 0, ventas = 0, fecha, año, mes, dia;
		char name [20], marca [20];
		producto *aux = *p;
		cout << "Ingrese el código del producto a eliminar: ";
		code = cinnum (0);
		if (code != -1 && buscarcode (*p, code)) {
			cout << "Ingrese el año de la eliminación (2000 - 2050): ";
			año = cinnum (0);
			if (año < 2000 || año > 2050) {
				cout << "Año inválido.\n\n";
				return;
			}
			cout << "Ingrese el mes de la eliminación (1 - 12): ";
			mes = cinnum (0);
			if (mes < 1 || mes > 12) {
				cout << "Mes inválido.\n\n";
				return;
			}
			cout << "Ingrese el día de la eliminación (1 - 31): ";
			dia = cinnum (0);
			if (dia < 1 || dia > 31) {
				cout << "Día inválido.\n\n";
				return;
			}
			fecha = año * 10000 + mes * 100 + dia;
			x = sino ();
			if (x != -1 && x) {
				if ((*p) -> codigo == code) {
					*p = aux -> sig;
					strcpy (name, aux -> nombre);
					strcpy (marca, aux -> marca);
					delete aux;
					cout << "\nProducto eliminado exitosamente!\n\n";
				}
				else {
					while (aux -> sig && aux -> sig -> codigo != code) aux = aux -> sig;
					if (aux -> sig) {
						producto *t = aux -> sig;
						aux -> sig = t -> sig;
						strcpy (name, t -> nombre);
						strcpy (marca, t -> marca);
						delete t;
						cout << "\nProducto eliminado exitosamente!\n\n";
					}
					else {
						cout << "No hay ningún producto con ese código.\nNo se eliminó ningún producto.\n\n";
						x = 0;
					}
				}
				if (x) {
					while (t) {
						total += eliminarprodventa (& (t -> prods), code, &ventas);
						t = t -> next;
					}
					FILE *file = fopen ("historico.txt", "a");
					fprintf (file, "%d\t%s\t%s\t%d\t%d\t%d\n", code, name, marca, total, ventas, fecha);
					fclose (file);
				}
			}
			else if (x != -1) cout << "\nNo se eliminó ningún producto.\n\n";
		}
	}
	else cout << "No hay productos para eliminar.\n\n";
}

void mostrarprod (producto *p, int pausa = 1) {
	if (p) {
		producto *aux = p;
		cout << "\t\t\t\t\t\tCódigo\t\t\tNombre\t\t\tMarca\n" << "\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		while (aux) {
			cout << "\t\t\t\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
			tabscalc (aux -> nombre);
			cout << aux -> marca << "\n";
			aux = aux -> sig;
		}
		cout << "\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
	}
	else cout << "No hay productos para mostrar.\n\n";
	if (pausa) system ("pause");
}

void modificarprod (producto *p) {
	if (p){
		int code, opt;
		char x [20] = "";
		producto *aux = p;
		cout << "Ingrese el código del producto a modificar: ";
		code = cinnum (0);
		if (code != -1)
			if (!buscarcode (p, code)) cout << "\nNo existe ningún producto con ese código.\n\n";
			else {
				while (aux && aux -> codigo != code) aux = aux -> sig;
				cout << "\n¿Qué desea modificar?\n\n1. Nombre\n2. Marca\n\nSu opción: ";
				opt = cinnum (0);
				cout << "\n";
				switch (opt) {
				case 1:
					cout << "Ingrese el nuevo nombre del producto: ";
					scanf ("%19[^\n\t]", x);
					bufc ();
					opt = sino ();
					if (opt && opt != -1) strcpy (aux -> nombre, x);
					break;
				case 2:
					cout << "Ingrese la nueva marca del producto: ";
					scanf ("%19[^\n\t]", x);
					bufc ();
					opt = sino ();
					if (opt && opt != -1) strcpy (aux -> marca, x);
					break;
				case -1:
					opt = 0;
					break;
				default:
					cout << "La opción elegida no existe.\n\n";
					opt = 0;
					break;
				}
				if (opt && opt != -1) cout << "\nCambio realizado exitosamente!\n\n";
				else cout << "\nNo se realizó ningún cambio.\n\n";
			}
	}
	else cout << "No hay productos para modificar.\n\n";
	system ("pause");
}

void agg_prod (producto **p) {
	int code, x;
	cout << "Ingrese un código para el producto: ";
	code = cinnum (0);
	if (code != -1)
		if (buscarcode (*p, code)) cout << "\nEl código ingresado ya pertenece a un producto, intente con uno diferente.\n\n";
		else {
			producto *ax = *p, *t = new producto;
			strcpy (t -> nombre, "");
			strcpy (t -> marca, "");
			t -> codigo = code;
			cout << "\nIngrese el nombre del producto: ";
			scanf ("%19[^\n\t]", t -> nombre);
			bufc ();
			cout << "\nIngrese la marca del producto: ";
			scanf ("%19[^\n\t]", t -> marca);
			bufc ();
			cout << "\n";
			x = sino ();
			if (x != -1 && x != 0) {
				if (*p)	while (ax -> sig && ax -> sig -> codigo < code) ax = ax -> sig;
				if (ax == *p) {
					if (ax && ax -> codigo < code) {
						t -> sig = ax -> sig;
						ax -> sig = t;
					}
					else {
						t -> sig = *p;
						*p = t;
					}
				}
				else {
					t -> sig = ax -> sig;
					ax -> sig = t;
				}
				cout << "\nProducto agregado exitosamente!\n\n";
			}
			else cout << "\nEl producto no se agregó.\n\n";
		}
	system ("pause");
}

//Procedimientos para tienda

void cargararchivotienda (FILE *file, tienda **p) {
	if (file && !feof (file)) {
		*p = new tienda;
		int prods, exis, min;
		fscanf (file, "%d\t%19[^\n\t]\t%19[^\n\t]\t%ld\t%d %d %d ", &((*p) -> codigo), &((*p) -> nombre), &((*p) -> direccion), &((*p) -> telefono), &prods, &exis, &min);
		if ((*p) -> codigo == -842150451) {delete *p; *p = NULL; fclose (file); return;}
		if (prods) {
			(*p) -> prods = new listaprods;
			(*p) -> prods -> ventas = NULL;
			listaprods *aux = (*p) -> prods;
			while (prods) {
				aux -> codigo = prods;
				aux -> existencia = exis;
				aux -> min = min;
				fscanf (file, "%d\t%d\t%d\t", &prods, &exis, &min);
				if (prods) aux -> prox = new listaprods;
				else aux -> prox = NULL;
				aux = aux -> prox;
			}
			fscanf (file, "\n");
		}
		else (*p) -> prods = NULL;
		cargararchivotienda (file, &((*p) -> next));
	}
	else {*p = NULL; if (file) fclose (file);}
}

void guardararchivotienda (FILE *file, tienda *p) {
	if (file && p) {
		listaprods *aux = p -> prods;
		fprintf (file, "%d\t%s\t%s\t%d\t", p -> codigo, p -> nombre, p -> direccion, p -> telefono);
		while (aux) {
			fprintf (file, "%d %d %d ", aux -> codigo, aux -> existencia, aux -> min);
			aux = aux -> prox;
		}
		fprintf (file, "0 0 0 ");
		if (p -> next) fprintf (file, "\n");
		guardararchivotienda (file, p -> next);
	}
	else if (!file) {cout << "Error guardando el archivo productos.txt.\n\n"; system ("pause");}
	else if (file) fclose (file);
}

tienda *existe_tienda (tienda *t, int code) {
    while (t) {
		if (t -> codigo == code) return t;
		t = t -> next;
	}
    return NULL;
}

void agg_tienda (tienda **t) {
	int code, x;
	cout << "Ingrese el código de la tienda que se va a agregar: ";
	code = cinnum (0);
	if (code != -1)
		if (existe_tienda(*t, code)) cout << "\nEl código ingresado ya pertenece a una tienda, intente con uno diferente.\n\n";
		else {
			tienda *ax = *t, *n = new tienda;
			strcpy (n -> nombre, "");
			strcpy (n -> direccion, "");
			n -> codigo = code;
			n -> prods = NULL;
			cout << "\nIngrese el nombre de la tienda: ";
			scanf ("%19[^\n\t]", n -> nombre);
			bufc ();
			cout << "\nIngrese la dirección de la tienda: ";
			scanf ("%19[^\n\t]", n -> direccion);
			bufc ();
			cout << "\nIngrese el teléfono de la tienda: ";
			n -> telefono = cinnum ();
			n -> prods = NULL;
			x = sino ();
			if (x != -1 && x != 0) {
				if (*t) while (ax -> next && ax -> next -> codigo < code) ax = ax -> next;
				if (ax == *t) {
					if (ax && ax -> codigo < code) {
						n -> next = ax -> next;
						ax -> next = n;
					}
					else {
						n -> next = *t;
						*t = n;
					}
				}
				else {
					n -> next = ax -> next;
					ax -> next = n;
				}
				cout << "\nTienda agregada exitosamente!\n\n";
			}
			else cout << "\nLa tienda no se agregó.\n\n";
		}
	system ("pause");
}

void consultar_tienda_por_código (tienda *t) {
	if (t) {
		int code;
		cout << "Ingrese el código de la tienda a consultar: ";
		code = cinnum (0);
		if (code != -1) {
			tienda *aux = t;
			while (aux && aux-> codigo != code) aux = aux->next;
			if (aux) {
				cout << "\n\t\t\t\t\tCódigo\t\t\tNombre\t\t\tDirección\t\tTeléfono\n" << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
				cout << "\t\t\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
				tabscalc (aux -> nombre);
				cout << aux -> direccion;
				tabscalc (aux -> direccion);
				cout << aux -> telefono << "\n";
				cout << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
			}
			else cout << "\nNo hay ninguna tienda con ese código.\n\n";
		}
	}
	else cout << "No hay tiendas para consultar.\n\n";
	system ("pause");
}

void transferir (listaprods **p, listaprods **t) {
	if (!*t || (*p) -> codigo < (*t) -> codigo) {
		listaprods *aux = (*t);
		*t = *p;
		*p = (*p) -> prox;
		(*t) -> prox = aux;
	}
	else if ((*p) -> codigo == (*t) -> codigo) {
		(*t) -> existencia += (*p) -> existencia;
		listaventas *aux = (*p) -> ventas, **tx = &((*t) -> ventas), *temp = NULL;
		listaprods *borrar = *p;
		if ((*t) -> ventas) {
			while (aux) {
				tx = &((*t) -> ventas);
				while (*tx && (*tx) -> fecha > aux -> fecha) tx = &((*tx) -> prox);
				temp = *tx;
				*tx = aux;
				aux = aux -> prox;
				(*tx) -> prox = temp;
			}
		}
		else (*t) -> ventas = (*p) -> ventas;
		*p = (*p) -> prox;
		delete borrar;
	}
	else transferir (p, &((*t) -> prox));
}

void eliminar_tienda(tienda **t) {
	if (*t) {
		int x, code, codetrans;
		tienda **aux = t, *temp = NULL;
		cout << "Ingrese el código de la tienda que se va a eliminar: ";
		code = cinnum (0);
		if (code != -1 && existe_tienda (*t, code)) {
			cout << "Ingrese el código de la tienda a la que va a transferir inventario: ";
			codetrans = cinnum (0);
			if (codetrans != code && codetrans != -1) {
				temp = existe_tienda (*t, codetrans);
				if (temp) {
					x = sino ("¿Seguro de que desea eliminar la tienda?");
					if (x != -1 && x) {
						while ((*aux) -> codigo != code) aux = &((*aux) -> next);
						while ((*aux) -> prods) transferir (&((*aux) -> prods), &(temp -> prods));
						temp = *aux;
						*aux = temp -> next;
						delete temp;
						cout << "Tienda eliminada exitosamente!\n\n";
					}
				}
				else if (codetrans != -1) cout << "No hay ninguna tienda con ese código\n\n";
			}
			else if (code == codetrans) cout << "No se puede transferir el inventario a la misma tienda.\n\n";
		}
		else if (code != -1) cout << "No hay ninguna tienda con ese código\n\n";
	}
	else cout << "No hay tiendas para eliminar.\n\n";
	system ("pause");
}

void mostrar_todas_tiendas(tienda *t, int pausa = 1){
    tienda *aux = t; 
	if (!aux) cout << "No hay tiendas para mostrar.\n\n";
	else {
		cout << "\t\t\t\t\tCódigo\t\t\tNombre\t\t\tDirección\t\tTeléfono\n" << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		while (aux) {
			cout << "\t\t\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
			tabscalc (aux -> nombre);
			cout << aux -> direccion;
			tabscalc (aux -> direccion);
			cout << aux -> telefono << "\n";
			aux = aux -> next;
		}
		cout << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
	}
	if (pausa) system ("pause");
}

void modificartienda (tienda *p) {
	if (p) {
		int code, opt;
		char x [20] = "";
		tienda *aux = p;
		cout << "Ingrese el código de la tienda que se va a modificar: ";
		code = cinnum (0);
		if (code != -1)
			if (!existe_tienda (p, code)) cout << "\nNo hay ninguna tienda con ese código.\n\n";
			else {
				while (aux && aux -> codigo != code) aux = aux -> next;
				cout << "\n¿Qué desea modificar?\n\n1. Nombre\n2. Dirección\n3. Teléfono\n\nSu opción: ";
				switch (cinnum (0)) {
				case 1:
					cout << "Ingrese el nuevo nombre de la tienda: ";
					scanf ("%19[^\n\t]", x);
					bufc ();
					cout << "\n";
					opt = sino ();
					if (opt && opt != -1) strcpy (aux -> nombre, x);
					break;
				case 2:
					cout << "Ingrese la nueva dirección de la tienda: ";
					scanf ("%19[^\n\t]", x);
					bufc ();
					cout << "\n";
					opt = sino ();
					if (opt && opt != -1) strcpy (aux -> direccion, x);
					break;
				case 3:
					cout << "Ingrese el nuevo teléfono de la tienda: ";
					code = cinnum (0);
					if (code != -1) {
						cout << "\n";
						opt = sino ();
						if (opt && opt != -1) aux -> telefono = code;
					}
					else opt = -1;
					break;
				case -1:
					opt = -1;
					break;
				default:
					cout << "La opción elegida no existe.\n\n";
					opt = 0;
					break;
				}
				if (opt != -1 && opt) cout << "\nCambio realizado exitosamente!\n\n";
				else if (opt != -1) cout << "\nNo se realizó ningún cambio.\n\n";
			}
	}
	else cout << "No hay tiendas para modificar.\n\n";
	system ("pause");
	system ("cls");
}

//Inventario

void mostrarinv (producto *p, listaprods *t) {
	if (t) {
		int x = 1;
		producto *aux;
		while (t) {
			if (!x) cout << "\t\t\t\t\t\t\t";
			consultarcode (p, t -> codigo, x, !x);
			cout << "\n";
			t = t -> prox;
			if (x) x = 0;
		}
		if (!x) cout << "\t\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
	}
	else cout << "No hay productos registrados.\n\n";
}

void actualizar (listaprods **p, int code) {
	if (*p)
		if ((*p) -> codigo != code && (*p) -> codigo < code) actualizar (&(*p)->prox, code);
		else if ((*p) -> codigo > code) {
			listaprods *aux = *p;
			(*p) = new listaprods;
			(*p) -> prox = aux;
			(*p) -> codigo = code;
			(*p) -> existencia = NULL;
			(*p) -> min = NULL;
			(*p) -> ventas = NULL;
			actualizar (p, code);
		}
		else {
			cout << "¿Qué desea actualizar?\n\n1. Existencia.\n2. Monto mínimo del producto.\n\nSu opción: ";
			int opt = cinnum (0), aceptar;
			switch (opt) {
			case 1:
				cout << "\nIngrese la nueva cantidad en existencia: ";
				opt = cinnum (0);
				if (opt != -1) {
					aceptar = sino ("¿Seguro de que desea realizar esta modificación?");
					if (aceptar && aceptar != -1) (*p) -> existencia = opt;
				}
				break;
			case 2:
				cout << "\nIngrese la nueva cantidad mínima en existencia: ";
				opt = cinnum (0);
				if (opt != -1) {
					aceptar = sino ("¿Seguro de que desea realizar esta modificación?");
					if (aceptar && aceptar != -1) (*p) -> min = opt;
				}
				break;
			case -1:
				break;
			default:
				cout << "\nLa opción que eligió no existe.\n\n";
				opt = -1;
				break;
			}
			if (opt == -1 || aceptar == -1 || aceptar == 0) cout << "No se realizó ningún cambio.\n\n";
			else cout << "Cambio realizado exitosamente!\n\n";
		}
	else {
		(*p) = new listaprods;
		(*p) -> prox = NULL;
		(*p) -> codigo = code;
		(*p) -> existencia = NULL;
		(*p) -> min = NULL;
		(*p) -> ventas = NULL;
		actualizar (p, code);
	}
}

void consexiscode (producto *t, listaprods *p, int code) {
	if (p)
		if (p -> codigo != code) consexiscode (t, p -> prox, code);
		else {
			while (t -> codigo != code) t = t -> sig;
			cout << "\t\t\tCódigo\t\t\tNombre\t\t\tMarca\t\t\tExistencia\t\tExistencia mínima\n" << "\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\t\t\t" << code << "\t\t\t" << t -> nombre;
			tabscalc (t -> nombre);
			cout << t -> marca;
			tabscalc (t -> marca);
			cout << p -> existencia << "\t\t\t" << p -> min << "\n\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
		}
	else cout << "\n\nNo hay informacion de ese producto en esta tienda.\n\n";
}

void consultar_existencia (producto *t, listaprods *p, int code) {
	if (p)
		if (p -> codigo != code) consultar_existencia (t, p -> prox, code);
		else {
			while (t -> codigo != code) t = t -> sig;
			cout << "\t\t\t\t\t\tCódigo\t\t\tNombre\t\t\tMarca\t\t\tExistencia\n" << "\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\t\t\t\t\t\t" << code << "\t\t\t" << t -> nombre;
			tabscalc (t -> nombre);
			cout << t -> marca;
			tabscalc (t -> marca);
			cout << p -> existencia << "\n\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n\n";
		}
	else cout << "\n\nNo hay informacion de ese producto en esta tienda.\n\n";
}

void mostrarexistencia (producto *p, listaprods *t) {
	if (t && p) {
		producto *aux;
		int menos = 0, total = 0;
		cout << "\t\t\tCódigo\t\t\tNombre\t\t\tMarca\t\t\tExistencia\t\tExistencia mínima\n" << "\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		while (t) {
			aux = p;
			while (aux && aux -> codigo != t -> codigo) aux = aux -> sig;
			cout << "\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
			tabscalc (aux -> nombre);
			cout << aux -> marca;
			tabscalc (aux -> marca);
			cout << t -> existencia << "\t\t\t" << t -> min;
			total += t -> existencia;
			if (t -> min > t -> existencia) {
				cout << "*";
				menos ++;
			}
			cout << "\n";
			t = t -> prox;
			aux = aux -> sig;
		}
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << total << "\t\t\t" << menos << "\n\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << "\n\n";
	}
	else if (p) cout << "No hay productos registrados en la tienda.\n\n";
	else cout << "No hay productos.\n\n";
}

//Ventas

void cargararchivoventas (FILE *file, tienda *p) {
	if (file && !feof (file) && p) {
		if (p -> prods) {
			listaprods *aux = p -> prods;
			char x;
			while (aux) {
				listaventas **px = &(aux -> ventas);
				*px = new listaventas;
				fscanf (file, "%d,%d\t", &((*px) -> cantidad), &((*px) -> fecha));
				while ((*px) -> cantidad && (*px) -> fecha) {
					px = &(*px) -> prox;
					*px = new listaventas;
					fscanf (file, "%d,%d\t", &((*px) -> cantidad), &((*px) -> fecha));
				}
				delete (*px);
				*px = NULL;
				fscanf (file, "%c", &x);
				if (x == '.') aux = aux -> prox;
				else {
					aux = NULL;
					cargararchivoventas (file, p -> next);
				}
			}
		}
		else cargararchivoventas (file, p -> next);
	}
	else if (file) fclose (file);
}

void guardararchivoventas (FILE *file, tienda *p) {
	if (file && p) {
		if (p -> prods) {
			listaprods *aux = p -> prods;
			while (aux) {
				listaventas *px = aux -> ventas;
				while (px) {
					fprintf (file, "%d,%d\t", px -> cantidad, px -> fecha);
					px = px -> prox;
				}
				fprintf (file, "0,0\t");
				aux = aux -> prox;
				if (aux) fprintf (file, ".");
			}
			if (p -> next) fprintf (file, ";\n");
			guardararchivoventas (file, p -> next);
		}
		else guardararchivoventas (file, p -> next);
	}
	else if (!file) {cout << "Error guardando el archivo productos.txt.\n\n"; system ("pause");}
	else fclose (file);
}

void mostrarexisventa (producto *p, listaprods *t, int tot = 0) {
	if (t && p) {
		producto *aux;
		int total = 0;
		cout << "\t\t\t\t\tCódigo\t\t\tNombre\t\t\tMarca\t\t\tExistencia\n" << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
		while (t) {
			aux = p;
			while (aux && aux -> codigo != t -> codigo) aux = aux -> sig;
			cout << "\t\t\t\t\t" << aux -> codigo << "\t\t\t" << aux -> nombre;
			tabscalc (aux -> nombre);
			cout << aux -> marca;
			tabscalc (aux -> marca);
			cout << t -> existencia;
			total += t -> existencia;
			cout << "\n";
			t = t -> prox;
			aux = aux -> sig;
		}
		if (tot) cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << total << "\n";
		cout << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

	}
	else if (p) cout << "No hay productos registrados en la tienda.\n\n";
	else cout << "No hay productos.\n\n";
}

void agregarventa (listaventas **p, int monto, int fecha) {
	if (*p && (*p) -> fecha > fecha) agregarventa (&((*p) -> prox), monto, fecha);
	else {
		listaventas *t = *p;
		*p = new listaventas;
		(*p) -> fecha = fecha;
		(*p) -> cantidad = monto;
		(*p) -> prox = t;
	}
}

int vender (listaprods *p, int code) {
	if (p)
		if (p -> codigo != code) vender (p -> prox, code);
		else if (p -> existencia > 0) {
			int monto, año, mes, dia, opt;
			cout << "Ingrese la cantidad de productos a vender (máximo " << p -> existencia << "): ";
			monto = cinnum (0);
			if (!monto) return 0;
			if (monto > p -> existencia) {
				cout << "El monto ingresado es mayor a la existencia del producto.\n\n";
				return 0;
			}
			else if (monto != -1 && monto < 0) {
				cout << "El monto ingresado es negativo.\n\n";
				return 0;
			}
			if (monto != -1) {
				cout << "Ingrese el año de la compra (2000 - 2050): ";
				año = cinnum (0);
				if (año < 2000 || año > 2050) {
					cout << "Año inválido.\n\n";
					return 0;
				}
				cout << "Ingrese el mes de la compra (1 - 12): ";
				mes = cinnum (0);
				if (mes < 1 || mes > 12) {
					cout << "Mes inválido.\n\n";
					return 0;
				}
				cout << "Ingrese el día de la compra (1 - 31): ";
				dia = cinnum (0);
				if (dia < 1 || dia > 31) {
					cout << "Día inválido.\n\n";
					return 0;
				}
				opt = sino ("¿Seguro de que desea realizar esta venta?");
				if (opt && opt != -1) {
					p -> existencia -= monto;
					agregarventa (&(p -> ventas), monto, año * 10000 + mes * 100 + dia);
					cout << "Producto vendido exitosamente!\n\n";
				}
				else return 0;
			}
		}
		else cout << "No hay producto en existencia para vender...\n\n";
	else cout << "\nEse producto no se encuentra registrado en la tienda.\n\n";
	return 1;
}

void ventcons (producto *t, listaprods *p, int code) {
	if (p)
		if (p -> codigo != code) consexiscode (t, p -> prox, code);
		else {
			while (t -> codigo != code) t = t -> sig;
			cout << "\n\n" << "Código\t\t\tNombre\t\t\tMarca\t\t\tExistencia\n" << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << code << "\t\t\t" << t -> nombre;
			tabscalc (t -> nombre);
			cout << t -> marca;
			tabscalc (t -> marca);
			cout << p -> existencia;
		}
	else cout << "\n\nNo hay informacion de ese producto en esta tienda.";
	cout << "\n\n";
}

//Reportes

void existenciamin (producto *p, tienda *tx) {
	if (p && tx) {
		int x = 2;
		tienda *t = NULL, *temp;
		while (tx) {
			tienda **aux = &t;
			while (*aux && strcmp ((*aux) -> nombre, tx -> nombre) < 0) aux = &(*aux) -> next;
			if (*aux && strcmp ((*aux) -> nombre, tx -> nombre) == 0)
				while (*aux && strcmp ((*aux) -> direccion, tx -> direccion) < 0) aux = &(*aux) -> next;
			temp = *aux;
			*aux = new tienda;
			(*aux) -> next = temp;
			(*aux) -> prods = tx -> prods;
			strcpy ((*aux) -> nombre, tx -> nombre);
			strcpy ((*aux) -> direccion, tx -> direccion);
			tx = tx -> next;
		}
		while (t) {
			if (t -> prods) {
				if (x == 2) x = 1;
				listaprods *aux = t -> prods;
				while (aux) {
					if (aux -> existencia <= aux -> min) {
						if (x) {
							cout << "Nombre Tienda\t\tDirección\t\tCódigo Producto\t\tNombre Producto\t\tMarca Producto\t\tExistencia\t\tExistencia mínima\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							x = 0;
						}
						cout << t-> nombre;
						tabscalc (t -> nombre);
						cout << t -> direccion;
						tabscalc (t -> direccion);
						consultarcode (p, aux -> codigo, 0);
						cout << aux -> existencia << "\t\t\t" << aux -> min << "\n";
					}
					aux = aux -> prox;
				}
			}
			t = t -> next;
		}
		if (x == 2) cout << "Ninguna tienda tiene productos.";
		else if (x) cout << "Ningún producto tiene menos del mínimo de existencia.";
		else cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
	}
	else if (!p && !tx) cout << "No hay productos ni tiendas.";
	else if (p) cout << "No hay tiendas.";
	else cout << "No hay productos.";
	cout << "\n\n";
}

int prodexistotal (char x [], producto *p, listaprods *t, int n) {
	if (t) {
		producto *px = buscarcode (p, t -> codigo);
		if (!strcmp (x, px -> nombre)) {
			if (n > 0) return -1;
			return t -> existencia + prodexistotal (x, p, t -> prox, n - 1);
		}
		else return prodexistotal (x, p, t -> prox, n - 1);
	}
	else return 0;
}

void existenciatot (producto *p, tienda *tx) {
	if (p && tx) {
		int x = 1, cont = 0, total;
		tienda *t = NULL, **aux = &t, *old = NULL;
		producto *px = NULL;
		listaprods *prx = NULL, **pry = NULL, *temp = NULL;
		while (tx) {
			aux = &t;
			while (*aux && strcmp ((*aux) -> nombre, tx -> nombre) < 0) aux = &((*aux) -> next);
			if (*aux && strcmp ((*aux) -> nombre, tx -> nombre) == 0)
				while (*aux && strcmp ((*aux) -> direccion, tx -> direccion) < 0) aux = &((*aux) -> next);
			old = *aux;
			*aux = new tienda;
			strcpy ((*aux) -> nombre, tx -> nombre);
			strcpy ((*aux) -> direccion, tx -> direccion);
			(*aux) -> prods = NULL;
			prx = tx -> prods;
			while (prx) {
				pry = &(*aux) -> prods;
				px = buscarcode (p, prx -> codigo);
				while (*pry && strcmp (buscarcode (p, (*pry) -> codigo) -> nombre, px -> nombre) < 0) pry = &((*pry) -> prox);
				temp = *pry;
				*pry = new listaprods;
				(*pry) -> prox = temp;
				(*pry) -> codigo = prx -> codigo;
				(*pry) -> existencia = prx -> existencia;
				prx = prx -> prox;
			}
			(*aux) -> next = old;
			tx = tx -> next;
		}
		while (t) {
			cont = 0;
			if (t -> prods) {
				prx = t -> prods;
				while (prx) {
					if (x) {
						cout << "\t\t\t\t\tNombre Tienda\t\tDirección\t\tNombre Producto\t\tExistencia\n\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
						x = 0;
					}
					px = buscarcode (p, prx -> codigo);
					total = prodexistotal (px -> nombre, p, t -> prods, cont);
					if (total != -1) {
						cout << "\t\t\t\t\t" << t -> nombre;
						tabscalc (t -> nombre);
						cout << t -> direccion;
						tabscalc (t -> direccion);
						cout << px -> nombre;
						tabscalc (px -> nombre);
						cout << total << "\n";
					}
					prx = prx -> prox;
					cont ++;
				}
			}
			t = t -> next;
		}
		if (x) cout << "Ninguna tienda tiene productos.";
		else cout << "\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	}
	else if (!p && !tx) cout << "No hay productos ni tiendas.";
	else if (p) cout << "No hay tiendas.";
	else cout << "No hay productos.";
	cout << "\n\n";
}

void prodsnoexis () {
	int code = 0, cant = 0, ventas = 0, fecha = 0, totc = 0, totv = 0, x = 1;
	char name [20] = "", marca [20] = "";
	FILE *file = fopen ("historico.txt", "r");
	while (file && !feof (file)) {
		fscanf (file, "%d\t%19[^\n\t]\t%19[^\n\t]\t%d\t%d\t%d\n", &code, &name, &marca, &cant, &ventas, &fecha);
		if (fecha && x) {
			cout << "Código\t\t\tNombre\t\t\tMarca\t\t\tTotal en depósito\tTotal de ventas\t\tFecha de salida de inventario\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
			x = 0;
		}
		if (fecha) {
			cout << code << "\t\t\t" << name;
			tabscalc (name);
			cout << marca;
			tabscalc (marca);
			cout << cant << "\t\t\t" << ventas << "\t\t\t" << fecha / 10000 << " " << (fecha % 10000) / 100 << " " << (fecha % 10000) % 100 << "\n";
			totc += cant;
			totv += ventas;
		}
	}
	if (code || cant || ventas || fecha) cout << "\t\t\t\t\t\t\t\t\t" << totc << "\t\t\t" << totv;
	else cout << "No hay productos que ya no se comercializan.";
	if (file) fclose (file);
	else cout << "No hay productos que ya no se comercializan.";
	cout << "\n\n";
}

void totprodstienda (producto *p, tienda *t) {
	producto *px = NULL;
	listaprods *tx = t -> prods;
	int total = 0, venta, x = 1;
	while (tx) {
		venta = cantidadventas (tx -> ventas, 0);
		if (x) {
			cout << "\t\t\t\t\t\tNombre\t\t\tMarca\t\t\tVentas\n" << "\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
			x = 0;
		}
		px = buscarcode (p, tx -> codigo);
		cout << "\t\t\t\t\t\t" << px -> nombre;
		tabscalc (px -> nombre);
		cout << px -> marca;
		tabscalc (px -> marca);
		cout << venta << "\n";
		total += venta;
		tx = tx -> prox;
	}
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << total;
	cout << "\n\n";
}

void ventasprod (producto *pd, listaprods *p, int code) {
	int x = 1, total = 0;
	while (p && p -> codigo != code) p = p -> prox;
	if (p) {
		producto *px = buscarcode (pd, p -> codigo);
		listaventas *aux = p -> ventas;
		while (aux) {
			if (x) {
				cout << "\t\t\t\t\t\tNombre\t\t\tMarca\t\t\tUnidades Vendidas\tFecha\n" << "\t\t\t\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
				x = 0;
			}
			cout << "\t\t\t\t\t\t" << px -> nombre;
			tabscalc (px -> nombre);
			cout << px -> marca;
			tabscalc (px -> marca);
			cout << aux -> cantidad << "\t\t\t" << (aux -> fecha) / 10000 << " " << ((aux -> fecha) % 10000) / 100 << " " << ((aux -> fecha) % 10000) % 100 << "\n";
			total += aux -> cantidad;
			aux = aux -> prox;
		}
		if (x) cout << "El producto no tiene ventas.";
		else cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << total;
	}
	else cout << "El código solicitado no existe.";
	cout << "\n\n";
}

int main () {
	producto *p = NULL;
	tienda *t = NULL, *inv = NULL, *temp = NULL;
	int x = 1, opt;
	setlocale(LC_CTYPE, "Spanish");
	system ("MODE 168, 45");
	cargararchivoproducto (fopen ("producto.txt", "r"), &p);
	cargararchivotienda (fopen ("tienda.txt", "r"), &t);
	cargararchivoventas (fopen ("ventas.txt", "r"), t);
	while (x) {
		encabezado ();
		cout << "\n";
		printcentrado ("Realizado por: ");
		cout << "\n\n";
		printcentrado ("Juan Mendoza C.I. 31.951.748    Elian López C.I. 31.867.990");
		cout << "\n";
		printcentrado ("Joseph Contreras C.I. 31.573.231    Andrés González C.I. 31.745.166");
		cout << "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
		printcentrado ("MENÚ PRINCIPAL");
		cout << "\n\n\t\t\t\t\t\t\t\t\t1. MANTENIMIENTO\n\t\t\t\t\t\t\t\t\t2. ACTUALIZACIÓN DE INVENTARIO\n\t\t\t\t\t\t\t\t\t3. VENTAS\n\t\t\t\t\t\t\t\t\t4. REPORTES\n\n\t\t\t\t\t\t\t\t\t0. Salir"
		<< "\n\n\t\t\t\t\t\t\t\t\t\tSu opción: "; 
		opt = cinnum ();
		system ("cls");
		switch (opt) {
		case 1:
			while (x) {
				encabezado ();
				printcentrado("1. MANTENIMIENTO");
				cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << "\n\t\t\t\t\t\t\t\t\t1. TIENDAS\n\t\t\t\t\t\t\t\t\t2. PRODUCTOS\n\n\t\t\t\t\t\t\t\t\t0. VOLVER AL MENÚ ANTERIOR" << "\n\n\t\t\t\t\t\t\t\t\t\tSu opción: ";
				opt = cinnum ();
				system ("cls");
				switch (opt) {
				case 1:
					while (x) {
						encabezado ();
						printcentrado ("1.1 MANTENIMIENTO TIENDAS");
						cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << "\n\t\t\t\t\t\t\t\t1. AGREGAR\n\t\t\t\t\t\t\t\t2. CONSULTAR\n\t\t\t\t\t\t\t\t3. MODIFICAR\n\t\t\t\t\t\t\t\t4. ELIMINAR\n\t\t\t\t\t\t\t\t5. MOSTRAR TODAS LAS TIENDAS\n\n\t\t\t\t\t\t\t\t0. Volver al menú anterior" << "\n\n\t\t\t\t\t\t\t\t\tSu opción: ";
						opt = cinnum ();
						system ("cls");
						if (opt) encabezado ();
						switch (opt) {
						case 1:
							printcentrado ("1.1.1 AGREGAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							agg_tienda (&t);
							break;
						case 2:
							printcentrado ("1.1.2 CONSULTAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							consultar_tienda_por_código (t);
							break;
						case 3:
							printcentrado ("1.1.3 MODIFICAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							modificartienda (t);
							break;
						case 4:
							printcentrado ("1.1.4 ELIMINAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							eliminar_tienda (&t);
							break;
						case 5:
							printcentrado ("1.1.5 MOSTRAR TODAS LAS TIENDAS");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							mostrar_todas_tiendas (t);
							break;
						case 0:
							x = 0;
							break;
						default:
							cout << "La opción que eligió no existe, intente nuevamente.\n\n";
							system ("pause");
							break;
						}
						system ("cls");
					}
					x = 1;
					system ("cls");
					break;
				case 2:
					while (x) {
						encabezado ();
						printcentrado ("1.2 MANTENIMIENTO PRODUCTOS");
						cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << "\n\t\t\t\t\t\t\t\t1. AGREGAR\n\t\t\t\t\t\t\t\t2. CONSULTAR POR CÓDIGO\n\t\t\t\t\t\t\t\t3. CONSULTAR POR NOMBRE\n\t\t\t\t\t\t\t\t4. MODIFICAR POR CÓDIGO\n\t\t\t\t\t\t\t\t5. ELIMINAR\n\t\t\t\t\t\t\t\t6. MOSTRAR TODOS LOS PRODUCTOS\n\n\t\t\t\t\t\t\t\t0. Volver al menú anterior" << "\n\n\t\t\t\t\t\t\t\t\tSu opción: ";
						opt = cinnum ();
						system ("cls");
						if (opt) encabezado ();
						switch (opt) {
						case 1:
							printcentrado ("1.2.1 AGREGAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							agg_prod (&p);
							break;
						case 2:
							printcentrado ("1.2.2 CONSULTAR POR CÓDIGO");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							if (p) {
								cout << "Ingrese el código del producto que desea consultar: ";
								opt = cinnum (0);
								cout << '\n';
								if (opt != -1) consultarcode (p, opt);
							}
							else cout << "No hay productos que consultar.\n\n";
							system ("pause");
							break;
						case 3:
							printcentrado ("1.2.3 CONSULTAR POR NOMBRE");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							consultarnombre (p);
							break;
						case 4:
							printcentrado ("1.2.4 MODIFICAR POR CÓDIGO");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							modificarprod (p);
							break;
						case 5:
							printcentrado ("1.2.5 ELIMINAR");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							eliminarprod (&p, t);
							system ("pause");
							break;
						case 6:
							printcentrado ("1.2.6 MOSTRAR TODOS LOS PRODUCTOS");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							mostrarprod (p);
							break;
						case 0:
							x = 0;
							break;
						default:
							cout << "\nLa opción que eligió no existe, intente nuevamente.\n\n";
							break;
						}
						system ("cls");
					}
					x = 1;
					system ("cls");
					break;
				case 0:
					x = 0;
					break;
				default:
					encabezado ();
					cout << "\nLa opción que eligió no existe, intente nuevamente.\n\n";
					system ("pause");
					break;
				}
				system ("cls");
			}
			system ("cls");
			x = 1;
			break;
		case 2:
			inv = NULL;
			while (x) {
				encabezado ();
				printcentrado ("2. INVENTARIO");
				cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
				encabezadoinv (inv);
				cout << "\n\t\t\t\t\t\t\t\t1. SELECCIONAR TIENDA\n\t\t\t\t\t\t\t\t2. AGREGAR/ELIMINAR PRODUCTO\n\t\t\t\t\t\t\t\t3. CONSULTAR EXISTENCIA DE UN PRODUCTO\n\t\t\t\t\t\t\t\t4. MOSTRAR TODA LA EXISTENCIA DE LA TIENDA\n\n\t\t\t\t\t\t\t\t0. VOLVER AL MENÚ ANTERIOR" << "\n\n\t\t\t\t\t\t\t\t\tSu opción: ";
				opt = cinnum ();
				system ("cls");
				encabezado ();
				switch (opt) {
				case 1:
					printcentrado ("2.1 SELECCIONAR TIENDA");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					mostrar_todas_tiendas (t, 0);
					if (t) {
						cout << "\n¿Qué tienda quiere seleccionar? (Escriba el código): ";
						x = cinnum (0);
						temp = inv;
						if (x != -1) {
							inv = existe_tienda (t, x);
							if (inv) {
								opt = sino ("¿Seguro de que desea elegir esta tienda?");
								if (opt && opt != -1) cout << "\nTienda elegida exitosamente!.\n\n";
								else inv = temp;
							}
							else {
								cout <<"\nNo existe ninguna tienda con ese código.\n";
								inv = temp;
							}
							if (inv == temp) cout << "\nNo se eligió ninguna tienda.\n\n";;
						}
						else inv = temp;
						x = 1;
					}
					system ("pause");
					system ("cls");
					break;
				case 2:
					printcentrado ("2.2 AGREGAR/ELIMINAR/ACTUALIZAR PRODUCTO");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					encabezadoinv (inv);
					if (inv) {
						mostrarprod (p, 0);
						cout << "\n¿Qué producto quiere agregar/eliminar/actualizar? (Escriba el código): ";
						x = cinnum (0);
						if (x != -1 && buscarcode (p, x)) actualizar (&(inv -> prods), x);
						else if (x != -1) cout << "Ese código de producto no existe.\n\n";
					}
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					x = 1;
					system ("pause");
					system ("cls");
					break;
				case 3:
					printcentrado ("2.3 CONSULTAR EXISTENCIA DE UN PRODUCTO");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					encabezadoinv (inv);
					if (inv) {
						mostrarinv (p, inv -> prods);
						if (inv -> prods) {
							cout << "\n¿Qué producto quiere consultar? (Escriba el código): ";
							x = cinnum (0);
							cout << '\n';
							if (x != -1 && buscarcode (p, x)) consexiscode (p, inv -> prods, x);
							else cout << "No hay ningun producto con ese código.\n\n";
						}
					}
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					x = 1;
					system ("pause");
					system ("cls");
					break;
				case 4:
					printcentrado ("2.4 MOSTRAR TODA LA EXISTENCIA DE LA TIENDA");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					encabezadoinv (inv);
					if (inv) mostrarexistencia (p, inv -> prods);
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					system ("pause");
					system ("cls");
					break;
				case 0:
					x = 0;
					break;
				default:
					cout << "\nLa opción que se eligió no existe, intente nuevamente.\n\n";
					system ("pause");
					break;
				}
				system ("cls");
			}
			system ("cls");
			x = 1;
			break;
		case 3:
			inv = NULL;
			while (x) {
				encabezado ();
				printcentrado ("3. VENTAS");
				cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
				encabezadoinv (inv);
				cout << "\n\t\t\t\t\t\t\t\t1. SELECCIONAR TIENDA\n\t\t\t\t\t\t\t\t2. VENDER PRODUCTO\n\t\t\t\t\t\t\t\t3. CONSULTAR EXISTENCIA DE UN PRODUCTO\n\t\t\t\t\t\t\t\t4. MOSTRAR TODA LA EXISTENCIA DE LA TIENDA\n\n\t\t\t\t\t\t\t\t0. VOLVER AL MENÚ ANTERIOR" << "\n\n\t\t\t\t\t\t\t\t\tSu opción: ";
				opt = cinnum ();
				system ("cls");
				encabezado ();
				switch (opt) {
				case 1:
					printcentrado ("3.1 SELECCIONAR TIENDA");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
					mostrar_todas_tiendas (t, 0);
					if (t) {
						cout << "\n¿Qué tienda quiere seleccionar? (Escriba el código): ";
						x = cinnum (0);
						temp = inv;
						if (x != -1) {
							inv = existe_tienda (t, x);
							if (inv) {
								opt = sino ("¿Seguro de que desea elegir esta tienda?");
								if (opt && opt != -1) cout << "\nTienda elegida exitosamente!.\n\n";
								else inv = temp;
							}
							else {
								cout <<"\nNo existe ninguna tienda con ese código.\n";
								inv = temp;
							}
							if (inv == temp) cout << "\nNo se eligió ninguna tienda.\n\n";;
						}
						else inv = temp;
					}
					system ("pause");
					break;
				case 2:
					printcentrado ("3.2 VENDER PRODUCTO");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					encabezadoinv (inv);
					if (inv) {
						mostrarexisventa (p, inv -> prods);
						if (inv -> prods) {
							cout << "\n¿Qué producto quiere vender? (Escriba el código): ";
							x = cinnum (0);
							if (x != -1 && !vender (inv -> prods, x)) cout << "No se agregó ninguna venta.\n\n";
						}
					}
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					x = 1;
					system ("pause");
					break;
				case 3:
					printcentrado ("3.3 CONSULTAR EXISTENCIA DE UN PRODUCTO");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					encabezadoinv (inv);
					if (inv){
						mostrarinv (p, inv -> prods);
						if (inv -> prods) {
							cout << "\n¿Qué producto quiere consultar? (Escriba el código): ";
							x = cinnum (0);
							if (x != -1) {
								cout << "\n";
								if (buscarcode (p, x)) consultar_existencia (p, inv -> prods, x);
								else cout << "No hay ningun producto con ese código.\n\n";
							}
						}
					}
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					x = 1;
					system ("pause");
					break;
				case 4:
					printcentrado ("3.4 MOSTRAR TODA LA EXISTENCIA DE LA TIENDA");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
					encabezadoinv (inv);
					if (inv) mostrarexisventa (p, inv -> prods);
					else cout << "No hay ninguna tienda seleccionada.\n\n";
					system ("pause");
					break;
				case 0:
					x = 0;
					break;
				default:
					cout << "\nLa opción que se eligió no existe, intente nuevamente.\n\n";
					system ("pause");
					break;
				}
				system ("cls");
			}
			system ("cls");
			x = 1;
			break;
		case 4:
			while (x) {
				encabezado ();
				printcentrado ("4. REPORTES");
				cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << "\n\t\t\t\t\t\t\t\t1. EXISTENCIA MÍNIMA EN TIENDAS\n\t\t\t\t\t\t\t\t2. EXISTENCIA TOTAL DE TIENDAS\n\t\t\t\t\t\t\t\t3. CONSULTAS POR TIENDA\n\t\t\t\t\t\t\t\t4. REPORTE DE PRODUCTOS QUE YA NO SE COMERCIALIZAN\n\n\t\t\t\t\t\t\t\t0. Volver al menú anterior" << "\n\n\t\t\t\t\t\t\t\t\tSu opción: ";
				opt = cinnum ();
				system ("cls");
				encabezado ();
				switch (opt) {
				case 1:
					printcentrado ("4.1 EXISTENCIA MÍNIMA EN TIENDAS");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					existenciamin (p, t);
					break;
				case 2:
					printcentrado ("4.2 EXISTENCIA TOTAL DE TIENDAS");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					existenciatot (p, t);
					break;
				case 3:
					printcentrado ("4.3 CONSULTAS POR TIENDA");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					inv = NULL;
					if (t) {
						mostrar_todas_tiendas (t, 0);
						cout << "\n¿Con qué tienda quiere trabajar? (Escriba el código): ";
						x = cinnum (0);
						if (x != -1) {
							inv = existe_tienda (t, x);
							if (inv) {
								cout << "\n\nTienda elegida exitosamente!.\n\n";
								system ("pause");
								system ("cls");
								encabezado ();
								printcentrado ("4.3 CONSULTAS POR TIENDA");
								cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							}
							else cout <<"\n\nNo existe ninguna tienda con ese código.\n\n";
						}
					}
					else cout << "No hay ninguna tienda para mostrar\n\n.";
					if (inv) {
						encabezadoinv (inv);
						cout<< "\n\t\t\t\t\t\t\t\t1. TOTAL POR PRODUCTO\n\t\t\t\t\t\t\t\t2. TOTAL DE VENTAS POR PRODUCTO-FABRICANTE EN LA TIENDA\n\t\t\t\t\t\t\t\t3. DETALLES DE VENTA DE UN PRODUCTO EN TIENDA\n\n\t\t\t\t\t\t\t\tSu opción: ";
						x = cinnum (0);
						if (x != -1) {
							system ("cls");
							encabezado ();
							encabezadoinv (inv);
						}
						switch (x) {
						case 1:
							printcentrado ("4.3.1 TOTAL POR PRODUCTO");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							mostrarexisventa (p, inv -> prods, 1);
							break;
						case 2:
							printcentrado ("4.3.2 TOTAL DE VENTAS POR PRODUCTO-FABRICANTE EN LA TIENDA");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							if (inv -> prods) totprodstienda (p, inv);
							else cout << "No hay productos registrados.\n\n";
							break;
						case 3:
							printcentrado ("4.3.3 DETALLES DE VENTA DE UN PRODUCTO EN TIENDA");
							cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
							mostrarinv (p, inv -> prods);
							if (inv -> prods) {
								cout << "\n¿Qué producto desea revisar? (Ingrese el código): ";
								x = cinnum (0);
								cout << '\n';
								if (x != -1) ventasprod (p, inv -> prods, x);
							}
							break;
						default:
							if (x != -1) cout << "\nLa opción que eligió no existe.\n\n";
							break;
						}
					}
					x = 1;
					break;
				case 4:
					printcentrado ("4.4 REPORTE DE PRODUCTOS QUE YA NO SE COMERCIALIZAN");
					cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
					prodsnoexis ();
					break;
				case 0:
					x = 0;
					break;
				default:
					cout << "\nLa opción que eligió no existe, intente nuevamente.\n\n";
					break;
				}
				if (x) system ("pause");
				system ("cls");
			}
			x = 1;
			system ("cls");
			break;
		case 0:
			x = 0;
			break;
		default:
			cout << "La opción que se eligió no existe, intente nuevamente.\n\n";
			system ("pause");
			break;
		}
		system ("cls");
	}
	guardararchivoproducto (fopen ("producto.txt", "w"), p);
	guardararchivotienda (fopen ("tienda.txt", "w"), t);
	guardararchivoventas (fopen ("ventas.txt", "w"), t);
}