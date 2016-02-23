La clase Entity sólo tiene como derivada Player, ya que el resto de objetos son demasiado similares entre sí
al ser tan sencillo el juego. En cualquier caso, se podrían añadir entidades derivadas sin tocar la lógica de World,
sólo haría falta que derivasen de Entity y añadirlas al array de m_entities.

Todas las operaciones sobre entidades se hacen con una misma llamada, excepto la comprobación de colisión entre jugador y objetos,
que se hace usando otro puntero a Player, por sencillez y legibilidad.

Vídeo: https://youtu.be/TEgQaG7IMbQ
Controles: Flechas del teclado para moverse, Enter para selección de menú.