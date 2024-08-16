#include <QCoreApplication>

#include <QFile>
#include <QDataStream>
#include <QtGlobal>
#include <QRandomGenerator>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <numeric>
//--------------------------------------------------------------------------------------------------------------------
int nomer=0;
//--------------------------------------------------------------------------------------------------------------------
struct Fraction {
    int numerator;
    int denominator;
 //  int nomer=0;
    Fraction() : numerator(0), denominator(1) {}
    
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denom == 0) throw std::invalid_argument("Знаменатель не может быть нулём.");
    }
    
    // Function to simplify the fraction
    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
    void print() const
    {
        std::cout<< nomer <<": " << numerator << "/" << denominator << std::endl;
      nomer++;
    }
 //int  nomer;++;
};
//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.
    
    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    //--------------------------------------------------------------------------------------------------------------------
    
    std::vector<Fraction> fractions;
    fractions.reserve(//0//
        10105
                      );
    
    for (int i = 0; i < 10105; ++i) {
        int numerator = QRandomGenerator::global()->bounded(1, 1000);
        int denominator;
        do {
            denominator = QRandomGenerator::global()->bounded(1, 1000);
        } while (denominator == 0);
        
        Fraction frac(numerator, denominator);
        frac.simplify();
        fractions.push_back(frac);
    }
    
    QFile file("/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi_drobi/sinapsi_drobi.bin");
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return -1;
    }
    
    QDataStream out(&file);
    for (const auto& fraction : fractions) {
        out << fraction.numerator << fraction.denominator;
    }
    
    file.close();
    std::cout << "Дроби были записаны в /home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi_drobi/sinapsi_drobi.bin" << std::endl;    
    //--------------------------------------------------------------------------------------------------------------------
    // Чтение из файла
    //  QFile file("fractions.bin");
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return -1;
    }
    
    QDataStream in(&file);
    while (!in.atEnd()) {
        int numerator;
        int denominator;
        in >> numerator >> denominator;
        Fraction frac(numerator, denominator);
        fractions.push_back(frac);
    }
    
    file.close();
   // int nomer=0;
    // Вывод всех считанных дробей в консоль
    for (const auto& fraction : fractions) {
       // nomer++;
   //   std::cout<< nomer <<": "  <<
            fraction.print();
 // nomer++;
    }    
//--------------------------------------------------------------------------------------------------------------------
    // Запись в текстовый файл
    QFile textFile("/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi_drobi/sinapsi_drobi.txt");
    if (!textFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Failed to open text file for writing" << std::endl;
        return -1;
    }
    
    QTextStream out2(&textFile);
    out2 << "Всего дробей сгенерировано: " << fractions.size() << "\n\n";
    for (const auto& fraction : fractions) {
        out2 << fraction.numerator << "/" << fraction.denominator << "\n";
    }
    
    textFile.close();
    
    std::cout << "Дроби записаны в /home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi_drobi/sinapsi_drobi.txt" << std::endl;    
//--------------------------------------------------------------------------------------------------------------------    
    return a.exec();
}
