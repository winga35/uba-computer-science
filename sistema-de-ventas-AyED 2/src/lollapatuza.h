#include "tipos.h"
#include "puesto.h"

using Personas = set<Persona>;
using Puestos = map<IdPuesto, puesto*>;
using GastoTotalPersonaAux = map<pair<Nat, Persona>, Nat>; //DiccLog(<dinero x persona>,dinero)
using GastoTotalPersona    = map<Persona, GastoTotalPersonaAux::iterator>; //DiccLog(persona,it)
using ProximoAHackear = map<Persona,map<Producto,map<IdPuesto,puesto*>>>;
using PersonaMayorGasto = GastoTotalPersonaAux::iterator;


class lollapatuza{
public:
    lollapatuza(Puestos p, Personas personas);
    void registrarVenta(IdPuesto id, Persona persona, Producto i, Cantidad c);
    void hackear(Persona persona, Producto i);
    const Personas personas() const;
    Puestos puestos()const;
    Nat idMenorStock(Producto i)const;
    Nat gastoTotal(Persona persona) const;
    Persona personaMayorGasto() const;
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;
    set<IdPuesto> idPuestos() const;

private:
    Personas _personas;
    Puestos _puestos;
    GastoTotalPersona _gastoTotalPersona;
    GastoTotalPersonaAux _gastoTotalPersonaAux;
    PersonaMayorGasto _personaMayorGasto;
    ProximoAHackear _proximoAHackear;
    set<IdPuesto> _idPuestos;
};
