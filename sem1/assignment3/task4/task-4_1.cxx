/****************************************************************************
Задача 4_1.

Напишите две функции для создания архива из одного файла и извлечения файла из архива.

    // Метод архивирует данные из потока original
    void Encode(IInputStream& original, IOutputStream& compressed);

    // Метод восстанавливает оригинальные данные
    void Decode(IInputStream& compressed, IOutputStream& original);

где:

    typedef char byte;

    interface IInputStream {
        // Возвращает false, если поток закончился
        virtual bool Read(byte& value) = 0;
    };

    interface IOutputStream {
        virtual void Write(byte value) = 0;
    };

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла в процентах от исходного.

Лучшие 3 решения из каждой группы оцениваются в 15, 10 и 5 баллов соответственно.

Пример минимального решения:

    #include "Huffman.h"

    static void copyStream(IInputStream&input, IOutputStream& output) {
        byte value;
        while(input.Read(value)) {
            output.Write(value);
        }
    }

    void Encode(IInputStream& original, IOutputStream& compressed) {
      copyStream(original, compressed);
    }

    void Decode(IInputStream& compressed, IOutputStream& original) {
        copyStream(compressed, original);
    }

****************************************************************************/

#include <iostream>

int main()
{
    return 0;
}

