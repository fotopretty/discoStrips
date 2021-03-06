#ifndef ANSWER_H
#define ANSWER_H

#include <Arduino.h>
using namespace std;

class Answer {
  public:
    Answer(int size)
    {
      buffer_size = size;
      buffer = new char[buffer_size];
      clear();
    }

    ~Answer()
    {
      delete[] buffer;
    }

    bool add(char* message, int len) {
      int index = 0;
      if ((buffer_size-current_length) < len)
      {
        return false;
      }

      for(int index=current_length; (index - current_length) < len; index++)
      {
        buffer[index] = message[index-current_length];
      }
      if(buffer[index] != '\0')
      {
        if(index < buffer_size)
        {
        }
        buffer[++index] = '\0';
      }

      current_length = index;
      return true;
    }

    bool add(String message)
    {
      // Compensate for \0
      int cpySize = message.length() + 1;
      if(cpySize > availableLength())
      {
        cpySize = availableLength();
      }
      message.toCharArray(&buffer[current_length], cpySize, 0);
      current_length += cpySize-1; // Minus \0
      return true;
    }

    void clear()
    {
      buffer[0] = '\0';
      current_length  = 0;
    }

    int size() { return buffer_size;}
    int currentLength() { return current_length;}
    int availableLength() { return (buffer_size-current_length);}

    char* getBuffer() { return buffer;}

  private:
    int buffer_size;
    int current_length;
    char* buffer;

};

#endif
