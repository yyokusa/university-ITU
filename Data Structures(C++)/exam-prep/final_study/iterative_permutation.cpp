#include <iostream>
#include <string>
using namespace std;
// https://en.wikipedia.org/wiki/Steinhaus%E2%80%93Johnson%E2%80%93Trotter_algorithm
// https://en.wikipedia.org/wiki/Heap%27s_algorithm
// Heap's Algorithm Paper -> https://watermark.silverchair.com/6-3-293.pdf?token=AQECAHi208BE49Ooan9kkhW_Ercy7Dm3ZL_9Cf3qfKAc485ysgAAAqMwggKfBgkqhkiG9w0BBwagggKQMIICjAIBADCCAoUGCSqGSIb3DQEHATAeBglghkgBZQMEAS4wEQQMlLyjXqc6VYI6P11mAgEQgIICVh-xrZp2pqsTJBDVbyLDlkDxPvntKKKBTKEuNd0bkS6bHpgTrVRNoNh12A3xVyqLGfTc2cbNi4X4dzJY21gAnqyvh_GU-M_7IXWyhpT0JtzGP9HEqCZp9GTWN0Lnbr-lThJMDSTMyN0_6yEU7oixexsPNj55R9qXRW42drWH-eudaWxEAcctfSZcZEnN7Pb29sY7wkznRA5OmWkj5E8pyk7lQG_Nm8kqwzUEogzCFM4NCQszGx3wTKa6xwu1WbkKKTNA4R-TIoLDD5x5y-gzIvKVwS26bBacIEhW-tphIKK8WfkaV84EY2pgCl_UvREmUgKzP7C8JnwunQjZSn6eOHg0zlj55Hnezsiw--LCxsa6xjwI3CeVXxT3IrLITig0Tnl-QPw_WcXMRJ2xRdZtfLOZCYQ9kgIJhilrrtte6yvyMS9YlVF3XIkcce8TB-iGojMOXg-PRrMf4a-lNpVg1ZcC69pkxeuK3nBtm7BfT04r6-B0qNEIqymsdldjRoMtwmIWPU-UFfr_oHmXC_Pol5vrPsAb4iWullvcCpH-LuW8tqiXEay0_9XVq5QPYjLI-_1dNU9VaYpzc-7-moaR6Wvttg2gXxUI0WZ0lAI2Y7yvmE1lCWhA-rh94NBM3MSMQcD389paXQmo8UDzBYapl7WlCyq7z4vS33WrvN_v6e0cXR-uOqpN_k62Ecge3bPGvl8gXJaYbf0f7b9J8SzYyfg-dln-MPgiMjrM4ools2fR449EL40EkeWlCbMa8WKNy98I1km1-rg_5lyF8wNbq33Hu9hzafs
//                  ABC
//          |             |                   |
//        A - A          A - B              A - C
//       ABC              BAC                CBA
//     |      |          |         |         |     |
//   B - B    B - C     A - A   C - A      B - B     B - A
//  ABC        ACB       BAC      BCA       CBA       CAB

void permutation(string&);
    
int main() {
    string str = "ABC";
    permutation(str);
    return 0;
}

void permutation(string& str) {
    for (size_t i = 0; i < str.size(); i++)
    {
        for (size_t j = 0; j < str.size(); j++)
        {
            if (i != j) {
                for (size_t k = 0; k < str.size(); k++)
                {
                    if (j != k && i != k) {
                        cout << str[i] << str[j] << str[k] << endl;
                    }
                }
            }
        }
    }
    
}