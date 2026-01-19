# 📦 Sistema de Gestión de Inventario (C++)

Este es un sistema de gestión de inventarios desarrollado en C++ utilizando conceptos de **Estructuras de Datos**. El proyecto permite administrar productos, tiendas, ventas y mantener un registro histórico mediante la persistencia de datos en archivos de texto.

## 👥 Autores
Este proyecto fue desarrollado por:
* Juan Mendoza
* Elian López
* Joseph Contreras
* Andrés Gonzales

## 🚀 Características
* **Gestión de Productos:** Manejo del catálogo mediante el archivo `producto.txt`.
* **Control de Sucursales:** Administración de datos de sedes en `tienda.txt`.
* **Módulo de Ventas:** Registro de transacciones en tiempo real en `ventas.txt`.
* **Persistencia:** Registro histórico de movimientos almacenado en `historico.txt`.

## 🛠️ Instalación y Configuración (Visual Studio 2012)

Para ejecutar el proyecto correctamente en un entorno de Visual Studio, siga estos pasos detallados:

1. **Crear el Proyecto:**
   * Abra Visual Studio 2012 y cree un **Nuevo proyecto vacío** de Visual C++.
   * Puede asignar el nombre que prefiera (por ejemplo, "Inventario_Estructuras").

2. **Preparar los Archivos:**
   * Cierre Visual Studio temporalmente.
   * Copie todos los archivos de la carpeta de datos (`main.cpp`, `producto.txt`, `tienda.txt`, `ventas.txt` e `historico.txt`) y péguelos directamente en la carpeta física donde se creó su nuevo proyecto.

3. **Vincular Archivos al IDE:**
   * Reabra el proyecto en Visual Studio.
   * En el **Explorador de Soluciones**, asegúrese de activar la opción "Mostrar todos los archivos".
   * Si los archivos aparecen con un icono de advertencia o no están integrados, haga clic derecho sobre cada uno y seleccione **Incluir en el proyecto**.
   * Es fundamental que el archivo `main.cpp` esté correctamente incluido para la compilación.

4. **Compilar y Ejecutar:**
   * Seleccione el **Depurador local de Windows** o presione la tecla `F5`. El sistema se abrirá en una consola de comandos.

## 🧠 Lógica de Funcionamiento
El sistema utiliza archivos planos para simular una base de datos persistente. La lógica de flujo sigue una regla de gestión de estados:
* **Derecha (+1):** Incrementa el registro, avanza en la transacción o guarda cambios.
* **Izquierda (-1):** Retrocede en los menús, cancela operaciones o elimina registros.

---
*Nota: Para un funcionamiento óptimo, asegúrese de que los archivos de texto (.txt) permanezcan en la misma ruta que el código fuente y el ejecutable generado.*
