#ifndef __ITENSOR_IQINDEXSET_H
#define __ITENSOR_IQINDEXSET_H
#include "iqindex.h"

//
// IQIndexSet
//
class IQIndexSet
    {
    public:

    IQIndexSet();

    IQIndexSet(const IQIndex& i1);

    IQIndexSet(const IQIndex& i1, const IQIndex& i2);

    IQIndexSet(const IQIndex& i1, const IQIndex& i2, const IQIndex& i3);

    IQIndexSet(IQIndex i1, IQIndex i2, 
               IQIndex i3, IQIndex i4,
               IQIndex i5 = IQIndex::Null(), 
               IQIndex i6 = IQIndex::Null(),
               IQIndex i7 = IQIndex::Null(), 
               IQIndex i8 = IQIndex::Null());

    IQIndexSet(std::vector<IQIndex>& iqinds);

    //
    // Accessor Methods
    //

    int
    r() const { return index_.size(); }

    const IQIndex&
    index(int j) const { return GET(index_,j-1); }

    int
    m(int j) const { return GET(index_,j-1).m(); }

    typedef std::vector<IQIndex>::const_iterator 
    index_it;

    //Can be used for iteration over Indices in a Foreach loop
    //e.g. Foreach(const IQIndex& I, t.index() ) { ... }
    const std::pair<index_it,index_it> 
    index() const  
        { return std::make_pair(index_.begin(),index_.end()); }

    Real
    uniqueReal() const { return ur_; }

    //
    // IQIndex Analysis
    //

    IQIndex 
    findtype(IndexType t) const;

    bool 
    findtype(IndexType t, IQIndex& I) const;

    int 
    findindex(const IQIndex& I) const;

    bool 
    has_common_index(const IQIndexSet& other) const;
    
    bool 
    hasindex(const IQIndex& I) const;

    bool 
    notin(const IQIndex& I) const { return !hasindex(I); }

    int
    minM() const;

    //
    // Primelevel Methods
    //

    void 
    noprime(PrimeType p = primeBoth);

    void 
    doprime(PrimeType pt, int inc = 1);

    void 
    primeall() { doprime(primeBoth,1); }

    void 
    primesite() { doprime(primeSite,1); }

    void 
    primelink() { doprime(primeLink,1); }

    void 
    mapprime(int plevold, int plevnew, PrimeType pt = primeBoth);

    void 
    mapprimeind(const IQIndex& I, int plevold, int plevnew, 
                PrimeType pt = primeBoth);

    void 
    primeind(const IQIndex& I, int inc = 1)
        { mapindex(I,primed(I,inc)); }

    void 
    primeind(const IQIndex& I, const IQIndex& J);

    void 
    noprimeind(const IQIndex& I) 
        { 
        IQIndex J(I);
        J.noprime();
        mapindex(I,J); 
        }

    //
    // Methods for Manipulating IQIndexSets
    //
    // Warning: these can overwrite other
    // Indices if not used properly
    //

    void 
    mapindex(const IQIndex& i1, const IQIndex& i2);

    void 
    addindex(const IQIndex& I);

    void 
    removeindex(int j);

    void
    setUniqueReal();

    void
    swap(IQIndexSet& other);

    void
    clear();

    //
    // Other Methods
    //

    void
    read(std::istream& s);

    void
    write(std::ostream& s) const;

    friend std::ostream&
    operator<<(std::ostream& s, const IQIndexSet& is);

    ENABLE_INTRUSIVE_PTR(IQIndexSet)

    //////////
    //
    // Data Members
    //

    std::vector<IQIndex> index_;

    Real ur_;

    mutable unsigned int 
    numref;

    //
    /////////

    };


#endif
