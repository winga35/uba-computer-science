module Documento
  ( Doc,
    vacio,
    linea,
    texto,
    foldDoc,
    (<+>),
    indentar,
    mostrar,
    imprimir,
  )
where

data Doc
  = Vacio
  | Texto String Doc
  | Linea Int Doc
  deriving (Eq, Show)

vacio :: Doc
vacio = Vacio

linea :: Doc
linea = Linea 0 Vacio

texto :: String -> Doc
texto t | '\n' `elem` t = error "El texto no debe contener saltos de línea"
texto [] = Vacio
texto t = Texto t Vacio

-- Ejercicio 1
foldDoc :: b -> (String -> b -> b) -> (Int -> b -> b) -> Doc -> b
foldDoc cVacio fTexto fLinea t = case t of
              Vacio     -> cVacio
              Texto s d -> fTexto s (rec d)
              Linea n d -> fLinea n (rec d)
            where rec = foldDoc cVacio fTexto fLinea

-- NOTA: Se declara `infixr 6 <+>` para que `d1 <+> d2 <+> d3` sea equivalente a `d1 <+> (d2 <+> d3)`
-- También permite que expresiones como `texto "a" <+> linea <+> texto "c"` sean válidas sin la necesidad de usar paréntesis.
-- Decidimos no crear tests para este ejercicio ya que la función está implicitamente testeada en el resto de ejercicios que utilizan foldDoc. De no tener el comportamiento esperado en el 
-- fold no hubieramos tenido los resultados esperados tanto en los tests como en el funcionamiento de los ejercicios.

infixr 6 <+>

-- Ejercicio 2

(<+>) :: Doc -> Doc -> Doc
(<+>) d1 d2 = case d2 of
  Texto s d -> foldDoc  d2                             
                      (\s1 rec -> if esTexto rec          
                                 then Texto (s1 ++ s) d  -- En caso de que hayan dos textos consecutivos, se juntan los strings en uno solo para cumplir invariante de representación.
                                 else Texto s1 rec)      -- Si no son dos textos, entonces por precondición ambos textos cumplen invariante y juntarlos no lo rompe.
                      Linea
                      d1
  _ -> foldDoc d2 Texto Linea d1     
  where esTexto (Texto s d) = True
        esTexto _ = False

-- Caso d2 = Texto s d:
-- Asumimos que d1 d2 cumplen el invariante por lo tanto los constructores Texto y Linea sobre sus elementos tambien lo cumplirán:
-- Hacemos foldDoc sobre d1. En el caso de que d1 termine en Texto s1 rec y rec también sea un Texto, se concatenan los strings s1 ++ s que sabemos que no va a ser vacío
-- o tener saltos de línea ya que ni s1 ni s son strings vacíos ni contienen saltos de línea. 
-- Como d se mantiene intacto, esto nos asegura que d va a ser Vacio o Linea ya que se forma un nuevo Texto (s1 ++ s) d.
-- Cuando el rec no es texto entonces se mantiene el constructor Texto s1 rec, lo cual garantiza que el invariante sigue valiendo.

-- Si d2 no es Texto (es Linea o Vacio):
-- Hacemos foldDoc sobre d1 con los constructores Texto y Linea directamente. Esto está permitido porque la combinación de documentos válidos mediante los mismos constructores 
-- preserva el invariante dado que en el caso Vacío se devuelve d2 y en el caso Linea no es necesario colisionar ambos strings en un solo constructor Texto.

--Ejercicio 3

indentar :: Int -> Doc -> Doc
indentar i = foldDoc Vacio Texto (\n acc -> Linea (n + i) acc)
-- Asumiendo que el documento al que se le aplica la función indentar cumple el invariante, podemos ver que 
-- en el caso Texto s d el invariante se preserva dado que no se modifica s ni d, simplemente se vuelve a aplicar el constructor. 
-- Nos resta ver el caso Linea, en el cual se suma una cantidad positiva de espacios a la indentación existente, lo cual
-- nos permite asegurar que la nueva cantidad siga siendo mayor o igual a 0.


--Ejercicio 4
mostrar :: Doc -> String
mostrar = foldDoc "" (++) (\i acc -> "\n"++ replicate i ' ' ++ acc)


imprimir :: Doc -> IO ()
imprimir d = putStrLn (mostrar d)

