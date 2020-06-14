#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "string.hpp"
#include "product.hpp"
#include "date.hpp"

Product *products;
int productsCount = 0;
Date today;
String file_path;
bool isSaved = true;
const String logs = "logs.txt";

String getOnlyFileExtension(String f)
{
    String extension;
    int i = f.length();
    while (f[i] != '.')
    {
        i--;
    }
    for (int j = 0; j < f.length() - i; j++)
    {
        extension = extension + f[j + (i + 1)];
    }
    return extension;
}

String getOnlyFileName(String f)
{
    String name;
    int i = f.length();
    while (f[i] != '\\' && i >= 0)
    {
        i--;
    }
    for (int j = 0; j < f.length() - i; j++)
    {
        name = name + f[j + (i + 1)];
    }
    return name;
}

void insertInListOfProducts(Product &product)
{
    int count = 0;
    double quantity = 0.0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].get_name() == product.get_name() && products[i].get_unit() == product.get_unit())
        {
            products[i].set_all_quantity(products[i].get_all_quantity() + product.get_quantity());
            // products[i].set_location(Location(products[i].get_unit(), products[i].get_name(), count));
            quantity += products[i].get_quantity();
            count++;
        }
    }
    product.set_all_quantity((double)(quantity + product.get_quantity()));
    //product.set_location(Location(product.get_unit(), product.get_name(), count));
    productsCount++;
    Product *cpy = new Product[productsCount];
    if (productsCount != 0)
    {
        std::copy(products, products + productsCount - 1, cpy);
        delete[] products;
    }
    cpy[productsCount - 1] = product;
    products = new Product[productsCount];
    std::copy(cpy, cpy + productsCount, products);
    delete[] cpy;
    std::pair<Date, int> *expiryDates = new std::pair<Date, int>[count + 1];
    int position = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].get_name() == product.get_name() && products[i].get_unit() == product.get_unit())
        {
            expiryDates[position++] = {products[i].get_expiry_date(), i};
        }
    }
    std::sort(expiryDates, expiryDates + position, [](auto date1, auto date2) {
        return !(date1.first > date2.first);
    });
    for (int i = 0; i < position; i++)
    {
        products[expiryDates[i].second].set_location(Location(product.get_unit(), product.get_name(), i));
    }
}

void openOrCreateFunc(String temp_file_path)
{
    if (!(getOnlyFileExtension(temp_file_path) == "txt"))
    {

        while (!(getOnlyFileExtension(temp_file_path) == "txt"))
        {
            std::cout << std::endl
                      << "This program is working only with .txt files!" << std::endl
                      << "Please, enter a valid file path!" << std::endl;
            std::cin >> temp_file_path;
        }
        std::cout << std::endl;
    }
    file_path = temp_file_path;
    delete[] products;
    productsCount = 0;
    products = new Product[productsCount];
    char readLine[100] = {'\0'};
    int count;
    std::ifstream in(file_path.getRawString());
    if (in.good())
    {
        in.getline(readLine, 100); // number of products
        if (!(String(readLine).get_word(0) == "Number"))
        {
            std::cout << "This is not a warehouse .txt file!" << std::endl
                      << "Give another path:" << std::endl;
            String temp;
            while (temp.length() == 0)
            {
                std::cin >> temp;
            }
            std::cout << std::endl;
            openOrCreateFunc(temp);
        }
        count = String(readLine).get_word(20).get_int();
        in.getline(readLine, 100); // new line
        for (int i = 0; i < count; i++)
        {
            Product product = Product();
            in.getline(readLine, 100); //name
            product.set_name(String(readLine).get_fromWord(2));
            //
            in.getline(readLine, 100); // expiry date
            product.set_expiry_date(Date(String(readLine).get_word(13).getRawString()));
            //
            in.getline(readLine, 100); // arrival date
            product.set_arrival_date(Date(String(readLine).get_word(14).getRawString()));
            //
            in.getline(readLine, 100); // manufacturer name
            product.set_manufacturer_name(String(readLine).get_fromWord(3));
            //
            in.getline(readLine, 100); // quantity and unit
            product.set_quantity(String(readLine).get_onWord(2).get_double());
            product.set_unit(String(readLine).get_onWord(3));
            //
            in.getline(readLine, 100); // all quantity
            in.getline(readLine, 100); // location
            in.getline(readLine, 100); // section
            in.getline(readLine, 100); // shelf
            in.getline(readLine, 100); // number
            //
            in.getline(readLine, 100); // comment
            product.set_comment(String(readLine).get_fromWord(2));
            //
            in.getline(readLine, 100); // new line
            insertInListOfProducts(product);
        }
        in.close();
    }
    isSaved = true;
    std::cout << std::endl
              << "Successfully opened " << getOnlyFileName(file_path) << std::endl;
}

void saveFile(String temp_file_path)
{
    std::ofstream out(temp_file_path.getRawString());
    out << "Number of products: " << productsCount << std::endl
        << std::endl;
    for (int i = 0; i < productsCount; i++)
    {
        out << products[i] << std::endl;
    }
    if (temp_file_path == file_path)
    {
        isSaved = true;
    }
    out.close();
    std::cout
        << "Successfully saved " << getOnlyFileName(temp_file_path) << std::endl
        << std::endl;
}

void saveLogs(String func, Product &product)
{
    std::ofstream logsOut(logs.getRawString(), std::ofstream::app);
    logsOut << file_path << std::endl;
    logsOut << today << std::endl;
    logsOut << func << std::endl;
    logsOut << product << std::endl;
    logsOut.close();
}

void openAndPrintLogs(Date from, Date to)
{
    std::cout << "Logs:" << std::endl
              << std::endl;
    char readLine[100] = {'\0'};
    int cnt = 0;
    //char buffer[100] = {'\0'};
    std::ifstream logsIn(logs.getRawString());
    while (logsIn.good())
    {
        logsIn.getline(readLine, 100);
        String path = readLine;
        if (path == file_path)
        {
            logsIn.getline(readLine, 100);
            Date d = Date(String(readLine).get_word(0).getRawString());
            if (d >= from && d <= to && d.isValid())
            {
                cnt++;
                std::cout << readLine << std::endl;
                for (int i = 0; i < 12; i++)
                {
                    logsIn.getline(readLine, 100);
                    std::cout << readLine << std::endl;
                }
                std::cout << std::endl;
                logsIn.getline(readLine, 100);
            }
        }
    }
    if (cnt == 0)
    {
        std::cout << "There aro no logs from the given period of time!" << std::endl
                  << std::endl;
    }
    logsIn.close();
}

void introFunc()
{
    std::cout << "Hello!" << std::endl
              << "Before proceeding with the program, tell me today's date in this format: [YYYY]-[MM]-[DD]" << std::endl;
    String sToday;
    do
    {
        std::cin >> sToday;
        today = Date(sToday.getRawString());
    } while (!today.isValid());
    std::cout << std::endl;
    std::cout << "          Open  /  Create new file  giving the path (directory and file name): " << std::endl
              << "Example:" << std::endl
              << "  > if you want a file in the program's folder        ->   <file_name>.txt" << std::endl
              << "  > if you want a file stored in different location   ->   C:\\Temp\\<file_name>.txt " << std::endl
              << "Path:" << std::endl;
    String temp_file_path;
    while (temp_file_path.length() == 0)
    {
        std::cin >> temp_file_path;
    }
    openOrCreateFunc(temp_file_path);
    std::cout << std::endl;
}

void printWarehouseOperFunc()
{
    std::cout << "Warehouse operations:" << std::endl
              << "> print" << std::endl
              << "> add" << std::endl
              << "> remove" << std::endl
              << "> clean" << std::endl
              << "> log <from> <to>" << std::endl
              << "> loss" << std::endl
              << "> open" << std::endl
              << "> close" << std::endl
              << "> save" << std::endl
              << "> saveas" << std::endl
              << "> help" << std::endl
              << "> exit" << std::endl
              << std::endl;
}

void readAndDoWarehouseOperFunc()
{
    while (true)
    {
        std::cout << "Command:" << std::endl;
        String line{};
        while (line.length() == 0)
        {
            std::cin >> line;
        }
        std::cout << std::endl;
        if (line.get_word(0) == "open")
        {
            if (line.get_onWord(2) == "")
            {
                std::cout << "You didn't give the path for the file!" << std::endl
                          << std::endl;
                continue;
            }
            if (!isSaved)
            {
                String yes_no;
                do
                {
                    std::cout << "Do you want to save the already opened file? (yes/no)" << std::endl;
                    std::cin >> yes_no;
                } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                if (yes_no.get_word(0) == "yes")
                {
                    saveFile(file_path);
                }
            }
            openOrCreateFunc(line.get_word(5));
            std::cout << std::endl;
            continue;
        }
        if (line.get_word(0) == "close")
        {
            if (!isSaved)
            {
                String yes_no;
                do
                {
                    std::cout << "Do you want to save the already opened file? (yes/no)" << std::endl;
                    std::cin >> yes_no;
                } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                if (yes_no.get_word(0) == "yes")
                {
                    if (productsCount == 0)
                    {
                        String yes_no;
                        do
                        {
                            std::cout << "There aren't any products in the warehouse, are you sure you want to save an empty file? (yes/no)" << std::endl;
                            std::cin >> yes_no;
                        } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                        if (yes_no.get_word(0) == "no")
                        {
                            std::cout << std::endl;
                            continue;
                        }
                    }
                    saveFile(file_path);
                }
            }
            std::cout << "Successfully closed " << getOnlyFileName(file_path) << std::endl;
            std::cout << "Open / Create new file  giving the path (directory and file name):" << std::endl;
            String temp_file_path;
            while (temp_file_path.length() == 0)
            {
                std::cin >> temp_file_path;
            }
            openOrCreateFunc(temp_file_path);
            std::cout << std::endl;
            continue;
        }
        if (line.get_word(0) == "save")
        {
            if (isSaved)
            {
                std::cout << "You've already saved this file!" << std::endl
                          << std::endl;
                continue;
            }
            if (productsCount == 0)
            {
                String yes_no;
                do
                {
                    std::cout << "There aren't any products in the warehouse, are you sure you want to save an empty file? (yes/no)" << std::endl;
                    std::cin >> yes_no;
                } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                if (yes_no.get_word(0) == "no")
                {
                    std::cout << std::endl;
                    continue;
                }
            }
            saveFile(file_path);
            continue;
        }
        if (line.get_word(0) == "saveas")
        {
            if (productsCount == 0)
            {
                String yes_no;
                do
                {
                    std::cout << "There aren't any products in the warehouse, are you sure you want to save an empty file? (yes/no)" << std::endl;
                    std::cin >> yes_no;
                } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                if (yes_no.get_word(0) == "no")
                {
                    std::cout << std::endl;
                    continue;
                }
            }
            if (line.get_onWord(2) == "")
            {
                std::cout << std::endl
                          << "You didn't give the path for the file!" << std::endl
                          << std::endl;
                continue;
            }
            String temp_file_path = line.get_onWord(2);
            if (!(getOnlyFileExtension(temp_file_path) == "txt"))
            {
                while (!(getOnlyFileExtension(temp_file_path) == "txt"))
                {
                    std::cout << "This program is working only with .txt files!" << std::endl
                              << "Please, enter a valid file path!" << std::endl;
                    std::cin >> temp_file_path;
                }
            }
            saveFile(temp_file_path);
            continue;
        }
        if (line.get_word(0) == "help")
        {
            std::cout << "The following commands are supported:" << std::endl
                      << std::endl
                      << "print             prints all products in the warehouse" << std::endl
                      << "add               adds product in the warehouse" << std::endl
                      << "remove            removes products by given name and quantity" << std::endl
                      << "clean             cleans the warehouse from all expired products" << std::endl
                      << "loss              shows the loss caused by expired product by given name," << std::endl
                      << "                  price per l/kg and a period of time" << std::endl
                      << "log <from> <to>   prints all the changes in the given period of time (*)" << std::endl
                      << "<from>            first date of the wanted period of time (*)" << std::endl
                      << "<to>              second date of the wanted period of time (*)" << std::endl
                      << "(*)               all dates are in this format: [YYYY]-[MM]-[DD]" << std::endl
                      << std::endl
                      << "open <file>       opens <file>" << std::endl
                      << "close             closes currently opened file" << std::endl
                      << "save              saves the currently opened file" << std::endl
                      << "saveas <file>     saves the currently opened file in <file>" << std::endl
                      << "help              prints this information" << std::endl
                      << "exit              exits this program" << std::endl
                      << "<file>            file path:" << std::endl
                      << "                        <file_name>.txt       > if you want a file in the program's folder" << std::endl
                      << "                        (only file name)" << std::endl
                      << "                              or" << std::endl
                      << "                    C:\\Temp\\<file_name>.txt   > if you want a file stored in different location" << std::endl
                      << "                   (directory and file name)" << std::endl
                      << std::endl;
            continue;
        }
        if (line.get_word(0) == "exit")
        {
            if (!isSaved)
            {
                String yes_no;
                do
                {
                    std::cout << "Do you want to save the already opened file? (yes/no)" << std::endl;
                    std::cin >> yes_no;
                } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                if (yes_no.get_word(0) == "yes")
                {
                    if (productsCount == 0)
                    {
                        String yes_no;
                        do
                        {
                            std::cout << "There aren't any products in the warehouse, are you sure you want to save an empty file? (yes/no)" << std::endl;
                            std::cin >> yes_no;
                        } while (!(yes_no.get_word(0) == "yes" || yes_no.get_word(0) == "no"));
                        if (yes_no.get_word(0) == "no")
                        {
                            std::cout << "Exiting the program...";
                            exit(0);
                        }
                    }
                    saveFile(file_path);
                }
                std::cout << std::endl;
            }
            std::cout << "Exiting the program...";
            exit(0);
        }
        if (line.get_word(0) == "print")
        {
            if (productsCount == 0)
            {
                std::cout << "There aren't any products in the warehouse!" << std::endl
                          << std::endl;
                continue;
            }
            for (int i = 0; i < productsCount; i++)
            {
                std::cout << products[i] << std::endl;
            }
            continue;
        }
        if (line.get_word(0) == "add")
        {
            Product product = Product();
            String n;
            String mn;
            String u;
            String c;
            String sd1;
            String sd2;
            String sq;
            Date d1;
            Date d2;
            double q;
            //
            std::cout << "   Add new product" << std::endl;
            //
            std::cout << "Name:" << std::endl;
            while (n.length() == 0)
            {
                std::cin >> n;
            }
            product.set_name(n);
            //
            do
            {
                std::cout << "Expiry date:" << std::endl;
                std::cin >> sd1;
                d1 = Date(sd1.getRawString());

            } while (sd1.length() == 0 || !sd1.isOnlyDateCharacters() || !d1.isValid());
            product.set_expiry_date(d1);
            //
            do
            {
                std::cout << "Arrival date:" << std::endl;
                std::cin >> sd2;
                d2 = Date(sd2.getRawString());

            } while (sd2.length() == 0 || !sd2.isOnlyDateCharacters() || !d2.isValid() || d2 > today);
            product.set_arrival_date(d2);
            //
            std::cout << "Manufacturer name:" << std::endl;
            while (mn.length() == 0)
            {
                std::cin >> mn;
            }
            product.set_manufacturer_name(mn);
            //
            std::cout << "Unit:" << std::endl;
            while (u.length() == 0)
            {
                std::cin >> u;
            }
            while (!(u == "kg" || u == "l" || u == ""))
            {
                std::cout << "Unit:" << std::endl;
                std::cin >> u;
            }
            product.set_unit(u);
            //
            do
            {
                std::cout << "Quantity:" << std::endl;
                std::cin >> sq;
                q = atof(sq.getRawString());
            } while (q < 0.0 || !sq.isOnlyNumbers() || sq.length() == 0);
            product.set_quantity(q);
            //
            std ::cout << "Comment:" << std::endl;
            while (c.length() == 0)
            {
                std::cin >> c;
            }
            product.set_comment(c);
            //
            insertInListOfProducts(product);
            saveLogs("   Add:", product);
            isSaved = false;
            std::cout << std::endl;
            continue;
        }
        if (line.get_word(0) == "remove")
        {
            if (productsCount == 0)
            {
                std::cout << "There aren't any products in the warehouse!" << std::endl
                          << std::endl;
                continue;
            }
            String n;
            String sq;
            double q;
            int cnt = 0;
            bool flag = false;
            std::cout << "   Remove" << std::endl;
            std::cout << "Name:" << std::endl;
            while (n.length() == 0)
            {
                std::cin >> n;
            }
            do
            {
                std::cout << "Quantity:" << std::endl;
                std::cin >> sq;
                q = atof(sq.getRawString());
            } while (q < 0.0 || !sq.isOnlyNumbers() || sq.length() == 0);
            std::cout << std::endl
                      << "Removed:" << std::endl
                      << std::endl;
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_name() == n)
                {
                    flag = true;
                    if (products[i].get_quantity() == q)
                    {
                        cnt++;
                        std::cout << products[i] << std::endl;
                        saveLogs("   Remove:", products[i]);
                    }
                }
            }
            if (cnt == 0)
            {
                std::cout << "There is no such product in the warehouse!" << std::endl
                          << std::endl;
                if (flag)
                {
                    std::cout << "These are all the products with the given name:" << std::endl
                              << std::endl;
                    for (int i = 0; i < productsCount; i++)
                    {
                        if (products[i].get_name() == n)
                        {
                            std::cout << products[i] << std::endl;
                        }
                    }
                }
                continue;
            }
            Product *cpy = new Product[productsCount - cnt];
            int countL = 0;
            int countKG = 0;
            String l = "l";
            String kg = "kg";
            int j = 0;
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_name() == n)
                {
                    if (products[i].get_quantity() == q)
                    {
                        continue;
                    }
                    else
                    {
                        products[i].set_all_quantity(products[i].get_all_quantity() - (cnt * q));
                    }
                    if (products[i].get_unit() == l)
                    {
                        countL++;
                    }
                    if (products[i].get_unit() == kg)
                    {
                        countKG++;
                    }
                }
                cpy[j++] = products[i];
            }
            delete[] products;
            productsCount = j;
            products = new Product[productsCount];
            std::copy(cpy, cpy + productsCount, products);
            delete[] cpy;
            std::pair<Date, int> *expiryDatesL = new std::pair<Date, int>[countL];
            std::pair<Date, int> *expiryDatesKG = new std::pair<Date, int>[countKG];
            int positionL = 0;
            int positionKG = 0;
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_name() == n && products[i].get_unit() == l)
                {
                    expiryDatesL[positionL++] = {products[i].get_expiry_date(), i};
                }
                if (products[i].get_name() == n && products[i].get_unit() == kg)
                {
                    expiryDatesKG[positionKG++] = {products[i].get_expiry_date(), i};
                }
            }
            std::sort(expiryDatesL, expiryDatesL + positionL, [](auto date1, auto date2) {
                return !(date1.first > date2.first);
            });
            std::sort(expiryDatesKG, expiryDatesKG + positionKG, [](auto date1, auto date2) {
                return !(date1.first > date2.first);
            });
            for (int i = 0; i < positionL; i++)
            {
                products[expiryDatesL[i].second].set_location(Location(l, n, i));
            }
            for (int i = 0; i < positionKG; i++)
            {
                products[expiryDatesKG[i].second].set_location(Location(kg, n, i));
            }
            isSaved = false;
            continue;
        }
        if (line.get_word(0) == "log")
        {
            if (line.get_onWord(2) == "" || line.get_onWord(3) == "")
            {
                std::cout << "Missing date   / log <to> <from> /" << std::endl
                          << std::endl;
                continue;
            }
            String sFrom = line.get_onWord(2);
            String sTo = line.get_onWord(3);
            Date from = Date(sFrom.getRawString());
            Date to = Date(sTo.getRawString());
            if (!sFrom.isOnlyDateCharacters() || !sTo.isOnlyDateCharacters() || !(from.isValid()) || !(to.isValid()) || from > to)
            {
                std::cout << "Invalid dates!" << std::endl;
                do
                {
                    std::cout << "From date:" << std::endl;
                    std::cin >> sFrom;
                    from = Date(sFrom.getRawString());
                } while (sFrom.length() == 0 || !sFrom.isOnlyDateCharacters() || !from.isValid());
                do
                {
                    std::cout << "To date:" << std::endl;
                    std::cin >> sTo;
                    to = Date(sTo.getRawString());
                } while (sTo.length() == 0 || !sTo.isOnlyDateCharacters() || !to.isValid() || from > to);
                std::cout << std::endl;
            }
            openAndPrintLogs(from, to);
            continue;
        }
        if (line.get_word(0) == "clean")
        {
            if (productsCount == 0)
            {
                std::cout << "There aren't any products in the warehouse!" << std::endl
                          << std::endl;
                continue;
            }
            int cnt = 0;
            std::cout << std::endl
                      << "Cleaned:" << std::endl
                      << std::endl;
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_expiry_date() <= today)
                {
                    cnt++;
                    std::cout << products[i] << std::endl;
                    saveLogs("   Clean:", products[i]);
                }
            }
            if (cnt == 0)
            {
                std::cout << "There are no expired products in the warehouse!" << std::endl
                          << std::endl;
                continue;
            }
            Product *cpy = new Product[productsCount - cnt];
            int j = 0;
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_expiry_date() <= today)
                {
                    for (int k = 0; k < productsCount; k++)
                    {
                        if (products[k].get_name() == products[i].get_name() && products[k].get_unit() == products[i].get_unit())
                        {
                            products[k].set_location(Location(products[k].get_unit(), products[k].get_name(), products[k].get_location().get_number() - 1));
                        }
                    }
                    continue;
                }
            }
            for (int i = 0; i < productsCount; i++)
            {
                if (products[i].get_expiry_date() <= today)
                {
                    continue;
                }
                cpy[j++] = products[i];
            }
            delete[] products;
            productsCount = j;
            products = new Product[productsCount];
            std::copy(cpy, cpy + productsCount, products);
            delete[] cpy;
            // std::pair<Date, int> *expiryDates = new std::pair<Date, int>[count + 1];
            // int position = 0;
            // for (int i = 0; i < productsCount; i++)
            // {
            //     if (products[i].get_name() == product.get_name() && products[i].get_unit() == product.get_unit())
            //     {
            //         expiryDates[position++] = {products[i].get_expiry_date(), i};
            //     }
            // }
            // std::sort(expiryDates, expiryDates + position, [](auto date1, auto date2) {
            //     return !(date1.first > date2.first);
            // });
            // for (int i = 0; i < position; i++)
            // {
            //     products[expiryDates[i].second].set_location(Location(product.get_unit(), product.get_name(), i));
            // }
            isSaved = false;
            continue;
        }
        if (line.get_word(0) == "loss")
        {
            String n;
            String sP;
            double p;
            String sFrom = "";
            String sTo = "";
            Date from;
            Date to;
            std::cout << "   Loss" << std::endl;
            std::cout << "Name:" << std::endl;
            while (n.length() == 0)
            {
                std::cin >> n;
            }
            do
            {
                std::cout << "Price per l/kg:" << std::endl;
                std::cin >> sP;
                p = atof(sP.getRawString());
            } while (p < 0.0 || !sP.isOnlyNumbers() || sP.length() == 0);
            std::cout << "From date:" << std::endl;
            do
            {
                std::cin >> sFrom;
                from = Date(sFrom.getRawString());
            } while (sFrom.length() == 0 || !sFrom.isOnlyDateCharacters() || !from.isValid());
            std::cout << "To date:" << std::endl;
            do
            {
                std::cin >> sTo;
                to = Date(sTo.getRawString());
            } while (sTo.length() == 0 || !sTo.isOnlyDateCharacters() || !to.isValid() || from > to);
            char readLine[100] = {'\0'};
            char buffer[100] = {'\0'};
            double loss = 0.0;
            std::ifstream logsIn(logs.getRawString());
            while (logsIn.good())
            {
                logsIn.getline(readLine, 100);
                String path = readLine;
                if (path == file_path)
                {
                    logsIn.getline(readLine, 100);
                    logsIn.getline(readLine, 100);
                    if (String(readLine) == "   Clean:")
                    {
                        logsIn.getline(readLine, 100);
                        if (String(readLine).get_fromWord(2) == n)
                        {
                            logsIn.getline(readLine, 100);
                            Date d = Date(String(readLine).get_word(13).getRawString());
                            if (d >= from && d <= to && d.isValid())
                            {
                                logsIn.getline(readLine, 100);
                                logsIn.getline(readLine, 100);
                                logsIn.getline(readLine, 100);
                                loss = (loss + String(readLine).get_onWord(2).get_double());
                            }
                        }
                    }
                }
            }
            logsIn.close();
            if (loss == 0)
            {
                std::cout << std::endl
                          << "There are no losses from this product in the given period of time" << std::endl
                          << std::endl;
                continue;
            }
            std::cout << std::endl
                      << "The loss from this product from " << from << " to " << to << " is " << loss * p << " lv." << std::endl
                      << std::endl;
            continue;
        }
        std::cout << "Wrong command" << std::endl
                  << std::endl;
    }
}

int main()
{
    introFunc();
    printWarehouseOperFunc();
    readAndDoWarehouseOperFunc();

    return 0;
}