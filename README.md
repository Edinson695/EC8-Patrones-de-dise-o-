# EC 8 - Patrones de Diseño 
---

 ## Pregunta 1: ¿Qué patrón desacopla qué parte del diseño?
 * Strategy: Desacopla el criterio de ordenamiento del flujo principal para la exportación de gastos
 * Factory desacopla la creación de exportadores de su uso
 * Decorator permite añadir las funcionalidades de audit/sum sin modificar las clases de exportación originales.