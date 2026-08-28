#include "puesto.h"
#include <algorithm>
#include <list>


using namespace std;

puesto::puesto(Stock s, Menu m, Promociones p) : _stock(s), _menu(m), _promociones(p)
{
    for (auto const &producto : p)
    {
        vector<int> cantidades;
        for (auto const &cant : producto.second)
        {
            cantidades.push_back(cant.first);
        }
        std::sort(cantidades.begin(), cantidades.end());
        _llavesPromociones.insert(pair<Producto,vector<int>>(producto.first,cantidades));
    }
};

puesto::~puesto()
{
}


/*Elegimos usar bucles foreach para iterar los diccionarios dado que nos parecio una manera mas prolija y declarativa de hacerlo.
En el TP2 habiamos usado whiles, con las correspondientes inicializaciones de los iteradores antes. Esta implementacion es equivalente
pero difiere en sintaxis.*/

Stock puesto::stockPuesto() const
{
    return _stock;
}

Menu puesto::menuPuesto()const
{
    return _menu;
}

Nat puesto::stockProducto(const Producto &producto)const
{
    return  _stock.at(producto);
}

Nat puesto::descuentoProducto(const Producto &producto, int cantidad) const
{
    if(_llavesPromociones.count(producto) == 0){
        return 0;
    }
    else
    {
    vector<int> cantidades = _llavesPromociones.at(producto);
    int c = calcularCantidad(cantidades, cantidad);
    if(c==0) return 0;
    return _promociones.at(producto).at(c);
    }
}

/*Hicimos un cambio respecto al TP2 dado que en el TP2 nuestra implementacion no estaba pensada para devolver los descuentos
  para items que no lo tuvieran explicitamente definido, ej si no habia descuento definido para cantidad 6, pero si para cantidad 4
  no devolvia nada, aunque lo correcto era que devuelva el mayor posible. Hicimos el cambio necesario para que ahora si lo haga.*/

Nat puesto::gastoPersona(Persona persona)const
{
    if(_gastoPersona.count(persona) == 0)
    {
        return 0;
    }
    else
    {
        return _gastoPersona.at(persona);
    }
}

Nat puesto::precioProducto(Producto producto) const
{
    return _menu.at(producto);
}
/*Hacemos que nos devuelva un Nat asi tenemos el dinero gastado en la venta
    y utilizamos ese valor para actualizar el gasto en lolla*/

pair<Nat,Nat> puesto::registrarVenta(Producto producto, Persona persona, Nat cantidad)
{
    int descuento = descuentoProducto(producto,cantidad);
    // Registrar la venta en compras con o sin descuento dependiendo si hay descuento disponible
    if (descuento == 0)
    {
        if (_comprasSinDescuento.count(persona) == 1)
        {
            if (_comprasSinDescuento.at(persona).count(producto) == 1)
            {
                _comprasSinDescuento.at(persona).at(producto).push_back(cantidad);
            }
            else
            {
                list<int> nuevaLista;
                nuevaLista.push_back(cantidad);
                _comprasSinDescuento.at(persona).insert(make_pair(producto,nuevaLista));
            }
        }
        else
        {
            list<int> nuevaLista;
            nuevaLista.push_back(cantidad);
            if(_comprasSinDescuento.count(persona) == 0)
            {
                _comprasSinDescuento.insert(make_pair(persona,map<Producto,list<int>>()));
                _comprasSinDescuento.at(persona).insert(make_pair(producto,nuevaLista));
            }
            else{
                _comprasSinDescuento.at(persona).insert(make_pair(producto,nuevaLista));
            }
        }
    }
    else
    {
        if (_comprasConDescuento.count(persona) == 1)
        {
            if (_comprasConDescuento.at(persona).count(producto) == 1)
            {
                _comprasConDescuento.at(persona).at(producto).push_back(cantidad);
            }
            else
            {
                list<int> nuevaLista;
                nuevaLista.push_back(cantidad);
                _comprasConDescuento.at(persona).insert(make_pair(producto,nuevaLista));
            }
        }
        else
        {
            list<int> nuevaLista;
            nuevaLista.push_back(cantidad);
            _comprasConDescuento[persona][producto] = nuevaLista;
        }
    }
    // Actualizar el stock y el gasto de la persona
    int gastoVenta = ((cantidad * precioProducto(producto)) * (100 - descuento)/100);
    int stockActualizado = _stock.at(producto) - cantidad;
    _stock[producto] = stockActualizado;

    if(_gastoPersona.count(persona) == 0)
    {
        _gastoPersona[persona] = gastoVenta;
    }
    else
    {
        int gastoActualizado = _gastoPersona.at(persona) + gastoVenta;
        _gastoPersona[persona] = gastoActualizado;
    }

    return make_pair(gastoVenta,descuento);
};

bool puesto::hackearPuesto(Producto producto, Persona persona)
{
    bool res = false;
    list<int> &listaCompras = _comprasSinDescuento.at(persona).at(producto);
    int cantidadActual = listaCompras.front();

    if ( cantidadActual == 1)
    {
        listaCompras.pop_front();
        if (listaCompras.empty())
        {
            res = true; // indica que hay que borrar el puesto del diccionario dicc(idPuesto,puesto) dentro de "ProximoaHackear" en la instancia de lollapatuza.
        }
    }
    else
    {
        listaCompras.pop_front();
        listaCompras.push_front(cantidadActual-1);
    }

    // Actualizar el gasto de la persona.
    Nat gastoActual = _gastoPersona.at(persona);
    Nat precioItem =  _menu.at(producto);
    _gastoPersona[persona] = gastoActual - precioItem;

    // Actualizar el stock
    Nat stockActualizado = _stock.at(producto) + 1;
    _stock[producto] = stockActualizado;

    return res;
}

//Dada un vector de ints y un int esta funcion retorna un res siguiendo la siguiente logica
//if ∃i:int(0<=i<tam(cants))->l cants[i] <= cant < cants[i+1] <-> res = cants[i] &&
//   cants[tam(cants)-1] <= cant -> res = cants[tam(cants-1)]                    &&
//   cants[0]            > cant -> res = 0
//

int puesto::calcularCantidad(vector<int> cants, int cant) const
{

    int tam = cants.size();

    if (tam == 0)
    {
        return 0;
    }
    else
    {
        if (cants[0] > cant)
        {
            return 0;
        }
        else
        {
            if (cants[tam - 1] <= cant)
            {
                return cants[tam - 1];
            }
            else
            {
                int inicio = 0;
                int final = tam - 1;
                while(inicio <= final)
                {
                    int mid = (inicio + final) / 2;

                    if (cants[mid] == cant)
                    {
                        return cants[mid];
                    }
                    else
                    {
                        if (cants[mid] < cant && cant < cants[mid + 1])
                        {
                            return cants[mid];
                        }
                        else
                        {
                            if (cants[mid] < cant)
                            {
                                inicio = mid + 1;
                            }
                            else
                            {
                                final = mid - 1;
                            }
                        }
                    }
                }
            }
        }
    }
}
