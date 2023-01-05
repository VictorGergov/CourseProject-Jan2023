#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
using namespace std;

class CTVSet
{
private:
    string m_strProducer;
    int m_iSize;
public:
    // 1.1 default constr.
    CTVSet() 
    {
        m_strProducer = "n/a";
        m_iSize = 0;
    }
    // 1.2 explicit constr.
    CTVSet(const CTVSet& tv) {
        m_strProducer = tv.m_strProducer;
       // m_strProducer = tv.m_iSize;
        m_iSize = tv.m_iSize;
    }
    // 1.3 copy constr.
    CTVSet(const string& strProducer, int iSize) 
    {
        m_strProducer = strProducer;
        m_iSize = iSize;
    }
    // 2.1 Functions
    int& GetSize() 
    {
        return m_iSize;
    }

    string& GetProducer() 
    {
        return m_strProducer;
    }

    // 2.2
    void output(ostream& toStream) 
    {
        toStream << "company " << GetProducer() << "size " << GetSize() << endl;
    }

    // 2.3
    void input(istream& fromStream)
    {
        fromStream >> GetProducer() >> GetSize();
    }
    
    // 3.1 operator
    void operator=(CTVSet& tv)
    {
        m_iSize = tv.m_iSize;
    }

    bool operator<(CTVSet& tv)
    {
        if (m_iSize < tv.m_iSize)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    bool operator==(CTVSet& tv)
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

    friend ostream& operator<<(ostream&, const CTVSet&);

    friend istream& operator>>(istream&, const CTVSet&);
};

ostream& operator<<(ostream& stream, const CTVSet&)
{
    CTVSet tv;
    tv.output(stream);
    return stream;
}
istream& operator>> (istream& stream, const CTVSet&)
{
    CTVSet tv;
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
    CTVSetShop()
    {

    }
    CTVSetShop(const m_vSales)
    {
        m_vSales = vSales;
    }

    // III.
    void WriteTo(ostream& stream)
    {
        copy(m_vSales.begin(), m_vSales.end(), ostream_iterator<CTVSet>(stream, "\n"));
    }

    void ReadIn(ifstream& stream)
    {
        if (m_vSales.size())
        {
            m_vSales.clear();
        }

        copy(istream_iterator<CTVSet>(stream), istream_iterator<CTVSet>(), back_inserter(m_vSales));
    }

    string maxSalesByProducer()
    {
        int max = 0;
        string mostSoldProducer = m_vSales[0].GetProducer();
        for (int i = 0; i < m_vSales.size(); i++)
        {
            int producerCount = (int)count(m_vSales.begin(), m_vSales.end(), m_vSales[i]);
                if (producerCount > max)
                {
                    max = producerCount;
                    mostSoldProducer = m_vSales[i].GetProducer();
                }
        }

        cout << mostSoldProducer << " " << max;
    }
    // I I. 3
    string maxSalesBySize()
    {
        int max = 0;
        int mostSoldSize = m_vSales[0].GetSize();
        for (int i = 0; i < m_vSales.size(); i++)
        {
            int sizeCount = (int)count(m_vSales.begin(), m_vSales.end(), m_vSales[i]);
            if (sizeCount > max)
            {
                max = sizeCount;
                mostSoldSize = m_vSales[i].GetSize();
            }
        }

        cout << mostSoldSize << " " << max;
    }

};


// I I I.
int main()
{
    CTVSetShop tvShop;
    CTVSet tv;

    tvShop.maxSalesByProducer();
    tvShop.maxSalesBySize();

    tv.GetProducer();
    tv.GetSize();
}

