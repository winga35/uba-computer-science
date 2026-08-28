module PPON where

import Documento


data PPON
  = TextoPP String
  | IntPP Int
  | ObjetoPP [(String, PPON)]
  deriving (Eq, Show)

--Ejercicio 5
pponAtomico :: PPON -> Bool
pponAtomico (TextoPP _) = True
pponAtomico (IntPP _) = True
pponAtomico _  = False

--Ejercicio 6
pponObjetoSimple :: PPON -> Bool
pponObjetoSimple (ObjetoPP xs) = all (\x -> pponAtomico (snd x)) xs
pponObjetoSimple _             = False

--Ejercicio 7
intercalar :: Doc -> [Doc] -> Doc
intercalar _ [] = vacio
intercalar d xs = foldr1 (\doc acc -> doc <+> d <+> acc) xs


entreLlaves :: [Doc] -> Doc
entreLlaves [] = texto "{ }"
entreLlaves ds =
  texto "{"
    <+> indentar
      2
      ( linea
          <+> intercalar (texto "," <+> linea) ds
      )
    <+> linea
    <+> texto "}"

-- Ejercicio 8

aplanar :: Doc -> Doc
aplanar = foldDoc vacio (\s acc -> texto s <+> acc) (\i acc -> texto " " <+> acc)

-- Ejercicio 9

pponADoc :: PPON -> Doc
pponADoc (TextoPP s) = texto (show s)
pponADoc (IntPP n) = texto (show n)
pponADoc (ObjetoPP xs) = if pponObjetoSimple (ObjetoPP xs) then aplanar (entreLlaves docs)
                         else entreLlaves docs
                         where
                          claveValorEnLinea :: (String, PPON) -> Doc
                          claveValorEnLinea (k,v) = texto (show k) <+> texto ": " <+> pponADoc v 
                          docs = map claveValorEnLinea xs
                          -- Recursión primitiva. En la condición del IF se está accediendo a las subestructuras del elemento cuando se hace pponObjetoSimple
                          -- sobre ObjetoPP xs, lo cual implica que NO puede ser recursión estructural. Luego, se hace recursión sobre la misma subestructura respetando el
                          -- esquema de recursión primitiva. Además, los casos base devuelven un valor fijo (TextoPP s muestra el texto, IntPP n muestra el número) 
                          -- que se puede observar en el esquema definido. Para completar la justificación, 
                          -- no estamos haciendo recursión sobre ninguna otra cosa que no sea la subestructura inmediata. No hay ningún uso de recursión fuera del patrón estructural del dato.
