La clase Entity s�lo tiene como derivada Player, ya que el resto de objetos son demasiado similares entre s�
al ser tan sencillo el juego. En cualquier caso, se podr�an a�adir entidades derivadas sin tocar la l�gica de World,
s�lo har�a falta que derivasen de Entity y a�adirlas al array de m_entities.

Todas las operaciones sobre entidades se hacen con una misma llamada, excepto la comprobaci�n de colisi�n entre jugador y objetos,
que se hace usando otro puntero a Player, por sencillez y legibilidad.

V�deo: https://youtu.be/TEgQaG7IMbQ
Controles: Flechas del teclado para moverse, Enter para selecci�n de men�.