:- use_module(piezas).

% Ejercicio 1: Sublista

% sublista(+Descartar, +Tomar, +L, -R)
sublista(Descartar, Tomar, L, R) :- 
    append(L1, L2 , L),         
    length(L1, Descartar),       
    append(R, _ , L2),           
    length(R, Tomar).            

% Ejercicio 12
% Mientras el tercer parámetro del predicado L esté instanciado, podemos garantizar que se generará un número finito de particiones L = L1 y L2 
% por la semántica del append/3. Luego, al llegar a length(L1,Descartar) tendremos en cada partición L1 instanciada por el append, 
% lo cual hará que length no genere infinitas soluciones para Descartar. Sabiendo esto, podemos decir que tanto append(R,_,L2) como
% length(R,Tomar) tendrán una cantidad finita de soluciones, ya que tendremos L2 instanciado y luego el predicado length tendrá tanto a R
% como a Tomar instanciados, lo cual hace que verifique la longitud. Por ende, el predicado puede usarse con R instanciado, Descartar sin instanciar
% y puede ser usado como sublista(-Descartar, +Tomar, +L, +R). 

% FIX:
% Teniendo en cuenta lo anterior veamos ahora que el resultado es correcto: Prolog dividira L en dos sublistas L1 y L2 por el comportamiento del append,
% luego instanciara en Descartar el tamanio correspondiente a L1.
% Entonces, llegado al segundo append es cuando verificara si R (que ya vino instanciada) es un prefijo de L2.
% Al ser R un prefijo de L2 ya sabemos justamente cual será la solución válida para L1, que es la sublista de L anterior al inicio de R (de tamaño Tomar).
% Con esto ya acotamos L1 y como anteriormente instanciamos Descartar en el tamanio de L1 Descartar será la solución válida.
% En caso de que le pasemos R instanciada pero R no cumpla con ser una sublista, lo que sucederá es que el append(R, _ , L2) no encontrará solución valida resultando en un false.


% Ejercicio 2: Tablero

% tablero(+K, -T)
tablero(K, T) :-
    length(T, 5),               
    maplist(filaLargoK(K), T).  
                                
% filaLargoK(+K, +Row)
filaLargoK(K, Row) :- length(Row,K).


% Ejercicio 3: Tamanio

% tamanio(+T, -F, -C).
tamanio(T, F, C) :- 
    length(T, F),               
    maplist(filaLargoK(C), T). 

% Ejercicio 4: Coordenadas

% coordenadas(+T, -IJ) 
coordenadas(T, IJ) :- 
    tamanio(T, 5, C),           
    IJ = (I,J),               
    between(1, 5, I),          
    between(1, C, J).          

% Ejercicio 5: K-Piezas

% combinaciones_ordenadas_size(+Size, +L1, ?L2)
combinaciones_ordenadas_size(0, _, []).
combinaciones_ordenadas_size(Size, [H|T], [H|R]) :-  
    Size > 0, M is Size - 1,                          
    length(T,LongitudT), LongitudT >= M,              % FIX: Condicion de corte para no probar combinaciones de mas 
    combinaciones_ordenadas_size(M, T, R).            
combinaciones_ordenadas_size(Size, [_|T], R) :-       
    length(T, LongitudT), LongitudT >= Size,          
    Size > 0,                                        
    combinaciones_ordenadas_size(Size, T, R).         

kPiezas(K, PS) :- 
    nombrePiezas(P),                                  
    combinaciones_ordenadas_size(K, P, PS).          


% Ejercicio 6: SeccionTablero

% seccionTablero(+T,+ALTO, +ANCHO, +IJ, ?ST).
seccionTablero(T, ALTO, ANCHO, (I, J), ST) :- 
    Imenos1 is I - 1,
    sublista(Imenos1, ALTO, T, Tparcial),           
    Jmenos1 is J - 1,
    maplist(sublista(Jmenos1, ANCHO),Tparcial, ST).
    

% Ejercicio 7: Ubicar pieza

% ubicarPieza(+Tablero, +Identificador) 
ubicarPieza(T, Identificador) :- 
    pieza(Identificador,Pieza),                             
    tamanio(Pieza, Filaspieza, Columnaspieza),              
    coordenadas(T,IJ),                                  
    seccionTablero(T,Filaspieza,Columnaspieza,IJ,TS),   
    TS = Pieza.     

% Ejercicio 8: Ubicar piezas

% ubicarPiezas(+Tablero, +Poda, +Identificadores)
ubicarPiezas(_, _, []).
ubicarPiezas(Tablero, Poda, [Identificador|Identificadores]) :- 
    ubicarPieza(Tablero,Identificador),                      
    poda(Poda, Tablero),                                     
    ubicarPiezas(Tablero, Poda, Identificadores).            
    

% Ejercicio 9: Llenar Tablero

% llenarTablero(+Poda, +Columna, -Tablero)
llenarTablero(Poda, Columnas, Tablero) :- 
    tablero(Columnas, Tablero),                     
    kPiezas(Columnas, Identificadores),            
    ubicarPiezas(Tablero, Poda, Identificadores).  
    

% Ejercicio 10: Medición

cantSoluciones(Poda, Columnas, N) :-
findall(T, llenarTablero(Poda, Columnas, T), TS),
length(TS, N).

% Resultados obtenidos:

% ?- time(cantSoluciones(sinPoda, 3, N)).
% 23,407,583 inferences, 1.163 CPU in 1.163 seconds (100% CPU, 20131487 Lips)
% N = 28.

% ?- time(cantSoluciones(sinPoda, 4, N)).
% 1,278,461,274 inferences, 65.581 CPU in 65.582 seconds (100% CPU, 19494396 Lips)
% N = 200.

% Ejercicio 11: Optimización

poda(sinPoda, _).           
poda(podaMod5, T) :- todosGruposLibresModulo5(T).

% todosGruposLibresModulo5(+Tablero)
todosGruposLibresModulo5(T) :-
    findall((I, J), coordenadaLibre(T, (I, J)), ListaLibres),    
    agrupar(ListaLibres, CoordenadasAgrupadas),                  
    not((member(Lista,CoordenadasAgrupadas), noEsMod5(Lista))).  % Fix: Versión con el not

noEsMod5(Grupo) :-
    length(Grupo, N),
    (N mod 5) =\= 0.

% coordenadaLibre(+T, -IJ)
coordenadaLibre(T, (I, J)) :-     
    coordenadas(T, (I, J)),         
    esCoordenadaLibre(T, (I, J)).   

esCoordenadaLibre(T, (I, J)) :- 
    nth1(I, T, Fila) ,             
    nth1(J, Fila, Casillero),       
    var(Casillero).                 

% Resultados obtenidos
% ?- time(cantSoluciones(podaMod5, 3, N)).
% 19,983,808 inferences, 1.048 CPU in 1.049 seconds (100% CPU, 19064639 Lips)
% N = 28.

% ?- time(cantSoluciones(podaMod5, 4, N)).
% 430,312,141 inferences, 22.729 CPU in 22.729 seconds (100% CPU, 18932694 Lips)
% N = 200.

% ?- time(cantSoluciones(podaMod5, 5, N)).
% 6,673,157,927 inferences, 355.238 CPU in 355.256 seconds (100% CPU, 18785046 Lips)
% N = 856.