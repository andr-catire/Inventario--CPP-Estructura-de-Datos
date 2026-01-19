# 📦 Sistema de Gestión de Inventario (C++)

Este es un sistema de gestión de inventarios desarrollado en C++ utilizando conceptos de **Estructuras de Datos**. [cite_start]El proyecto permite administrar productos, tiendas, ventas y mantener un registro histórico mediante la persistencia de datos en archivos de texto[cite: 142].

## 👥 Autores
[cite_start]Este proyecto fue desarrollado por[cite: 1]:
* Juan Mendoza
* Elian López
* Joseph Contreras
* Andrés Gonzales

## 🚀 Características
* [cite_start]**Gestión de Productos:** Manejo del catálogo mediante `producto.txt`[cite: 163, 223].
* [cite_start]**Control de Sucursales:** Administración de datos en `tienda.txt`[cite: 179, 224].
* [cite_start]**Módulo de Ventas:** Registro de transacciones en `ventas.txt`[cite: 180, 225].
* [cite_start]**Persistencia:** Registro histórico de movimientos en `historico.txt`[cite: 155, 221].

## 🛠️ Instalación y Configuración (Visual Studio 2012)

[cite_start]Para correr el proyecto correctamente, siga estos pasos basados en la documentación oficial[cite: 2]:

1. [cite_start]**Crear el Proyecto:** * Abra Visual Studio 2012 y cree un **Nuevo proyecto vacío** de Visual C++[cite: 3, 61, 130].
   * [cite_start]Puede nombrarlo como desee (ej. "prueba")[cite: 93].
2. **Preparar los Archivos:**
   * [cite_start]Cierre Visual Studio y pegue todos los archivos de la carpeta "archivos de datos" dentro de la carpeta física de su nuevo proyecto[cite: 142].
   * [cite_start]Los archivos principales deben incluir: `main.cpp`, `producto.txt`, `tienda.txt`, `ventas.txt` e `historico.txt`[cite: 142, 188].
3. **Vincular en el IDE:**
   * Reabra el proyecto en Visual Studio.
   * [cite_start]En el **Explorador de Soluciones**, active la opción "Mostrar todos los archivos"[cite: 188].
   * [cite_start]Haga clic derecho sobre los archivos que aparezcan con un círculo rojo y seleccione **Incluir en el proyecto**[cite: 188, 232].
   * [cite_start]Repita este proceso para todos los archivos, especialmente para `main.cpp`[cite: 243, 244].
4. **Compilar y Ejecutar:**
   * [cite_start]Utilice el botón **Depurador local de Windows** o presione F5 para iniciar el sistema[cite: 213].

## 🧠 Lógica de Funcionamiento
[cite_start]El sistema utiliza archivos planos para simular una base de datos persistente[cite: 142]. La lógica sigue un flujo de control donde:
* **Derecha (+1):** Aumenta el registro o avanza en la gestión de datos.
* **Izquierda (-1):** Retrocede o elimina registros según la ley de flujo definida.

---
[cite_start]*Nota: Asegúrese de que los archivos .txt estén en la misma ruta que el ejecutable para que la carga de datos sea exitosa[cite: 187, 188].*
