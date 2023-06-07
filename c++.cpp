
#include <iostream>
#include <map>

class JSArray
{
private:
  int lastIndex;
  std::map<int, void *> map;

  JSArray *concate(int start, JSArray *arr)
  {
    std::map<int, void *> soursMap = map;
    for (int i = 0; i < arr->getCapasity(); i++)
    {
      map[start] = arr->pop();
    }
    arr->setMap(map);
    map = soursMap;
    return arr;
  }

  void setMap(std::map<int, void *> mapp)
  {
    map = mapp;
  }
  std::map<int, void *> getMap()
  {
    return map;
  }

public:
  JSArray()
  {
    lastIndex = 0;
  }
  void push(void *value)
  {
    map[lastIndex++] = value;
  }

  void *pop()
  {
    return map[--lastIndex];
  }
  int getCapasity()
  {
    return lastIndex;
  }
  void *get(int index)
  {
    return map[index];
  }

  JSArray *concate(JSArray *arr)
  {
    return concate(lastIndex, arr);
  }
  JSArray *slice(int startIndex, int endIndex)
  {
    JSArray *tmp = new JSArray;
    for (int i = startIndex, j; i <= endIndex; i++)
    {
      tmp->push(map[i]);
    }
    return tmp;
  }
  JSArray *splice(int start, int length)
  {
    concate(start, slice(length + start, lastIndex));
    return slice(start, start + length);
  }

  void *shift()
  {
    void *returnVal = map[0];
    map = slice(1, lastIndex)->getMap();
    --lastIndex;
    return returnVal;
  }
  void *unshift()
  {
    void *returnVal = map[lastIndex];
    map = slice(1, lastIndex)->getMap();
    --lastIndex;
    return returnVal;
  }
};

int main(void)
{
  JSArray *arr = new JSArray;

  int ii = 9;
  double dd = 1.2;
  std::string str = "Hello : The day starts at 6:30";
  int *i = &ii;
  double *d = &dd;
  std::string *st = &str;
  arr->push(i);
  arr->push(d);
  arr->push(st);

  arr->getCapasity();
  arr->get(2);
  JSArray *tmp = arr->concate(arr->slice(0, 1));
  JSArray *tmp1 = arr->concate(arr->splice(0, 1));
  tmp->shift();
  tmp->unshift();

  std::cout << *(std::string *)arr->pop() << std::endl;
  std::cout << *(double *)arr->pop() << std::endl;
  std::cout << *(int *)arr->pop() << std::endl;
  return 0;
}