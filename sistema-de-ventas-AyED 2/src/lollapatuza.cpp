#include "lollapatuza.h"

lollapatuza::lollapatuza(Puestos p, Personas personas): _personas(personas), _puestos(p)
{
    // Armar la lista de todos los items posibles recorriendo todos los puestos
    set<Producto> items;
    for(auto puestoActual:p) // O(A*I)
    {
        Menu menuActual = puestoActual.second->stockPuesto();
        for(auto itemActual:menuActual)
        {
            items.insert(itemActual.first);
        }
    }

    // Definir para todas las personas los items correspondientes.
    for(Persona pers:personas) //O(P*I)
    {
        _proximoAHackear.insert(make_pair(pers,map<Producto,map<IdPuesto,puesto*>>()));
        for(Producto itemActual:items)
        {
            _proximoAHackear.at(pers).insert(make_pair(itemActual,map<IdPuesto,puesto*>())) ;
        }
    }

    // Definir todas las personas en gastoTotalPersonaAux y gastoTotalPersona
    for (Persona pers : personas)
    {
        auto it = _gastoTotalPersonaAux.insert({{0, pers}, 0});
        _gastoTotalPersona.insert(make_pair(pers,it.first));
    }

    // Armar el conjunto de idPuestos
    for (auto puesto:p)
    {
        _idPuestos.insert(puesto.first);
    }

    // Definir el mayor gastador como la persona de menor ID
    _personaMayorGasto = _gastoTotalPersonaAux.begin();

};


void lollapatuza:: registrarVenta(IdPuesto id, Persona persona, Producto producto, Cantidad cantidad)
{
    // Obtener la instancia de puesto
    puesto* puestoActual = _puestos.at(id);
    Nat precio = puestoActual->menuPuesto()[producto];

    // Registrar la venta en el puesto y obtener el valor de la venta
    pair<Nat,Nat> gastoVentaYDescuento = puestoActual->registrarVenta(producto,persona,cantidad);
    Nat gastoVenta = gastoVentaYDescuento.first;

    // Registrar el nuevo gasto de la persona
    auto itGastoActual = _gastoTotalPersona.at(persona); //El .at devuelve el iterador al diccionario gastoTotalPersonaAux
    Nat gastoActual = itGastoActual->second; 
    _gastoTotalPersonaAux.erase(itGastoActual);
    pair<Nat,Persona> clave = make_pair(gastoActual+gastoVenta,persona);
    itGastoActual = _gastoTotalPersonaAux.insert(pair<pair<Nat,Persona>,Nat>(clave,gastoActual+gastoVenta)).first;
    _gastoTotalPersona[persona] = itGastoActual; // Definir la persona

    // Actualizar el proximo a hackear
    Nat descuento = gastoVentaYDescuento.second;
    if (descuento == 0 && _proximoAHackear.at(persona).at(producto).count(id) == 0)
    {
        _proximoAHackear.at(persona).at(producto).insert(make_pair(id,puestoActual));
    }

    // Actualizar la persona de mayor gasto
    _personaMayorGasto = prev(_gastoTotalPersonaAux.end());
}

void lollapatuza:: hackear(Persona persona, Producto producto)
{
    auto iteradorDiccPuesto = _proximoAHackear.at(persona).at(producto).begin();
    puesto* puestoAHackear = iteradorDiccPuesto->second;
    IdPuesto idPuestoAHackear = iteradorDiccPuesto->first;

    bool puestoVacio = puestoAHackear->hackearPuesto(producto, persona);

    // Si no quedaron mas compras actualizar el proximo a hackear
    if (puestoVacio)
    {
        _proximoAHackear.at(persona).at(producto).erase(idPuestoAHackear);
    }

    // Actualizar el gasto de la persona, y la persona de mayor gasto
    Nat precioItem = puestoAHackear->precioProducto(producto);
    Nat gastoActual = _gastoTotalPersona.at(persona)->second;
    Nat gastoActualizado = gastoActual - precioItem;

    auto itMayorGastoActual = _personaMayorGasto;

    _gastoTotalPersonaAux.erase(_gastoTotalPersona.at(persona));
    auto iteradorActualizado = _gastoTotalPersonaAux.insert(make_pair(make_pair(gastoActualizado, persona), gastoActualizado)).first;
    _gastoTotalPersona.erase(persona);
    _gastoTotalPersona.insert(make_pair(persona, iteradorActualizado));

    // Actualizar la persona de mayor gasto
    _personaMayorGasto = prev(_gastoTotalPersonaAux.end());
}

/*Respecto a la implementacion original del TP2, algunas funciones pasaron de ser un void a devolver un valor, como por ejemplo al registrar venta/hackear.
 * Estos valores que son devueltos por las funciones son utilizados para modificar cosas en la instancia de lollapatuza sin necesidad de hacer un acceso mas
 * al puesto para obtenerlos. Mas alla de que haciendo este acceso cumpliriamos la complejidad pedida por el enunciado, consideramos que es una buena
 * implementacion, dado que no complica mucho los algoritmos, y los hace mas eficientes.*/

const Personas lollapatuza::personas()const
{
    return _personas;
}

Puestos lollapatuza::puestos()const
{
    return _puestos;
}

Nat lollapatuza::idMenorStock(Producto i)const
{
    auto iteradorAPuesto = _puestos.begin();
    Nat menorStock = iteradorAPuesto->second->stockProducto(i);
    IdPuesto idMenor = iteradorAPuesto->first;

    for(auto p:_puestos)
    {
        if(p.second->stockProducto(i) < menorStock)
        {
            menorStock = p.second->stockProducto(i);
            idMenor = p.first;
        }
    }
    return idMenor;
}

Nat lollapatuza::gastoTotal(Persona persona) const
{
    if(_gastoTotalPersona.count(persona) == 1)
    {
        auto iteradorAGasto = _gastoTotalPersona.at(persona);
        return iteradorAGasto->first.first;
    }
    else
    {
        return 0;
    }
}

Persona lollapatuza::personaMayorGasto() const
{
    auto a = _personaMayorGasto;
    return a->first.second;
}

Nat lollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const
{
    puesto* puestoActual = _puestos.at(idPuesto);
    return puestoActual->stockProducto(producto);
}

Nat lollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const
{
    puesto* puestoActual = _puestos.at(idPuesto);
    return puestoActual->descuentoProducto(producto,cantidad);
}

Nat lollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const
{
    puesto* puestoActual = _puestos.at(idPuesto);
    return puestoActual->gastoPersona(persona);
}

set<IdPuesto> lollapatuza::idPuestos() const
{
    return  _idPuestos;
}


