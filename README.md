# 📦 Sistema de Gestión de Inventario (C++)

Este es un sistema de gestión de inventarios desarrollado en C++ utilizando conceptos de **Estructuras de Datos**. El proyecto permite administrar productos, tiendas, ventas y mantener un registro histórico mediante la persistencia de datos en archivos de texto.

## 🚀 Características

* **Gestión de Productos:** Altas, bajas y modificaciones de artículos.
* **Control de Tiendas:** Administración de diferentes sucursales o puntos de inventario.
* **Módulo de Ventas:** Registro de transacciones en tiempo real.
* **Persistencia de Datos:** Carga y guardado automático en archivos `.txt` para no perder la información al cerrar el programa.
* **Reportes:** Generación de informes en formato PDF (según documentación adjunta).

## 📁 Estructura del Proyecto

* `main.cpp`: Punto de entrada del programa y lógica principal.
* `Archivos de datos/`: Carpeta que contiene la base de datos en texto plano:
    * `producto.txt`: Catálogo de artículos.
    * `tienda.txt`: Información de sucursales.
    * `ventas.txt`: Registro de operaciones.
    * `historico.txt`: Log histórico de movimientos.
* `Informe proyecto de estructuras.pdf`: Documentación técnica detallada.

## 🛠️ Instalación y Ejecución

### Requisitos Previos
* Compilador de C++ (GCC/G++ o similar).
* Git (para clonar el repositorio).

### Pasos para ejecutar

1. **Clonar el repositorio:**
   ```bash
   git clone [https://github.com/andr-catire/Inventario--CPP-Estructura-de-Datos.git](https://github.com/andr-catire/Inventario--CPP-Estructura-de-Datos.git)
   cd Inventario--CPP-Estructura-de-Datos
