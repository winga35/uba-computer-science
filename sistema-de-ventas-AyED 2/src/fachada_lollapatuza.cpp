#include "fachada_lollapatuza.h"

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos)
{
    map<IdPuesto, puesto*> diccPuestos;
    map<IdPuesto ,aed2_Puesto>::const_iterator It;
    for (It = infoPuestos.begin(); It != infoPuestos.end() ; ++It)
    {
        aed2_Puesto puestoFachada = It->second;
        puesto* nuestraInstancia = new puesto(puestoFachada.stock,puestoFachada.menu,puestoFachada.promociones);
        diccPuestos.insert(make_pair(It->first,nuestraInstancia));
    }

    _l = new lollapatuza(diccPuestos,personas);
};

FachadaLollapatuza::~FachadaLollapatuza()
{
    for (auto p:_l->puestos())
    {
        delete p.second;
    }

    delete _l;
}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _l->registrarVenta(idPuesto,persona,producto,cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto)
{
    _l->hackear(persona,producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const
{
    return _l->gastoTotal(persona);
}

Persona FachadaLollapatuza::mayorGastador() const
{
    return _l->personaMayorGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const
{
   return _l->idMenorStock(producto);
}

const set<Persona> FachadaLollapatuza::personas() const
{
    return _l->personas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const
{
    return _l->stockEnPuesto(idPuesto,producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const 
{
    return _l->descuentoEnPuesto(idPuesto,producto,cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const
{
    return _l->gastoEnPuesto(idPuesto,persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const
{
    return _l->idPuestos();
}