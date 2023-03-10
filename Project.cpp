#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
using namespace std;

class CTVSet
{
private:
    string m_strProducer;
    int m_iSize;
public:
    // 1.1 default constr.
    CTVSet() = default;                // default constructor
    // 1.3 copy constructor
    CTVSet(const CTVSet& other) = default; // copy constructor
    // 3.1.
    CTVSet& operator=(const CTVSet& other) = default; // copy assignment 
    // 1.2 explicid constr.
    CTVSet(const string& strProducer, int iSize) 
    {
        m_strProducer = strProducer;
        m_iSize = iSize;
    }
    // 2.1 Functions
    int GetSize() 
    {
        return m_iSize;
    }

    string GetProducer() 
    {
        return m_strProducer;
    }

    // 2.2
    void output(ostream& toStream) 
    {
        toStream << "company " << GetProducer() << ", size " << GetSize() << endl;
    }

    // 2.3
    void input(istream& fromStream)
    {
        fromStream >> m_strProducer >> m_iSize;
    }
    
    // 3.1 operator
   
    bool operator<(CTVSet& tv)
    {
        return m_iSize < tv.m_iSize;
    }

    bool operator>(CTVSet& tv)
    {
        return m_iSize > tv.m_iSize;
    }

    bool operator==(const CTVSet& tv) const
    {
        if (m_iSize == tv.m_iSize)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(CTVSet& tv) {
        return m_iSize != tv.m_iSize;
    }

    friend ostream& operator<<(ostream&, const CTVSet&);

    friend istream& operator>>(istream&, const CTVSet&);
};

ostream& operator<<(ostream& stream, CTVSet& tv)
{
    tv.output(stream);
    return stream;
}
istream& operator>> (istream& stream, CTVSet& tv)
{
    tv.input(stream);
    return stream;
}

class CTVSetShop
{
private:
    vector<CTVSet>m_vSales;
public:
    CTVSetShop(const CTVSetShop& tvShop)
    {
        m_vSales = tvShop.m_vSales;
    }

    CTVSetShop(const vector<CTVSet>& tvs)
    {
        m_vSales = tvs;
    }

    CTVSetShop()
    {

    }
    

    // III.
    void WriteTo(ostream& stream)
    {
        for (CTVSet tv : m_vSales) {
            tv.output(stream);
        }
    }

    void ReadIn(istream& stream, int n)
    {
        for (size_t i = 0; i < n; i++)
        {
            CTVSet tv;
            cout << "Enter {producer size}: ";
            stream >> tv;
            m_vSales.push_back(tv);
        }
    }

    string maxSalesByProducer()
    {
        map<string, int> salesByProducer;
        for (CTVSet tv : m_vSales) {
            if (salesByProducer.find(tv.GetProducer()) == salesByProducer.end()) {
                // doesnt exist in map
                salesByProducer.insert({ tv.GetProducer(), 1 });
            }
            else {
                salesByProducer[tv.GetProducer()]++;
            }
        }

        int maxSales = 0;
        string maxProducer = "";

        map<string, int>::iterator it;

        for (it = salesByProducer.begin(); it != salesByProducer.end(); it++)
        {
            if (it->second > maxSales) {
                maxSales = it->second;
                maxProducer = it->first;
            }
        }

        return maxProducer + " " + to_string(maxSales);

      
    }
    // I I. 3
    string maxSalesBySize()
    {
        map<int, int> salesBySize;
        for (CTVSet tv : m_vSales) {
            if (salesBySize.find(tv.GetSize()) == salesBySize.end()) {
                // doesnt exist in map
                salesBySize.insert({ tv.GetSize(), 1 });
            }
            else {
                salesBySize[tv.GetSize()]++;
            }
        }

        int maxSales = 0;
        int maxSize = -1;

        map<int, int>::iterator it;

        for (it = salesBySize.begin(); it != salesBySize.end(); it++)
        {
            if (it->second > maxSales) {
                maxSales = it->second;
                maxSize = it->first;
            }
        }

        return to_string(maxSize) + " " + to_string(maxSales);
        
    }

};


// I I I.
int main()
{

    cout << "How many tvs?: ";
    int n;
    cin >> n;
    
    CTVSetShop* tvShop = new CTVSetShop();

    tvShop->ReadIn(cin, n);

    cout << "Maximum sales by producer:" << endl;
    cout << tvShop->maxSalesByProducer() << endl;

    cout << "Maximum sales by size: " << endl;
    cout << tvShop->maxSalesBySize() << endl;

    cout << "List of all TV Sets: " << endl;
    tvShop->WriteTo(cout);  
}