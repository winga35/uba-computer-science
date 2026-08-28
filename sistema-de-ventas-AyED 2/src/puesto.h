#include "tipos.h"

using LlavesPromociones = map<Producto, vector<int>>;
using Compras = map<Persona,map<Producto,list<int>>>; // Para hacer compras con y sin descuento
using Gasto = map<Persona,Nat>;

class puesto{
public:
    puesto(Stock s, Menu m, Promociones p);
    ~puesto();
    Nat stockProducto(const Producto& producto)const;
    Nat descuentoProducto(const Producto& producto, int cantidad)const;
    Nat gastoPersona(Persona persona) const;
    Nat precioProducto (Producto producto) const;
    pair<Nat,Nat> registrarVenta (Producto producto, Persona persona, Nat cantidad);
    Stock stockPuesto()const;
    Menu menuPuesto()const;
    bool hackearPuesto(Producto producto, Persona persona); // Devuelve false si no hay que actualizar el dicc, true si hay que actualizarlo

    /*En registrarVenta ,a diferencia de nuestro diseño (que no tiene return) devolvemos una tupla<gasto de la venta,descuento del producto>
      Como una especie de ticket que nos facilita luego la implemenación, es decir, nos ahorra el paso extra de volver
      a buscar dichos elementos para así poder utilizarlos en las demas funciones.*/

private:
    Stock _stock;                        // Stock
    Promociones _promociones;            // Descuentos
    LlavesPromociones _llavesPromociones;  // Cantidad de Descuentos Disponibles
    Compras _comprasSinDescuento;        // Compras con descuento
    Compras _comprasConDescuento;        // Compras sin descuento
    Gasto _gastoPersona;                 // Gasto por persona
    Menu _menu;                          // Precios

    int calcularCantidad(vector<int> cants, int cant)const;
};

