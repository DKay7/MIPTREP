
class Lin{
  public:
   int cm; // сантиметры
   int mm; // миллиметры
};

void printLin(Lin a)
{
    printf ("%d %d", a.cm, a.mm);
    return;
}

Lin convertToLin(int kletki)
{
    Lin lin;
    lin.cm = (kletki / 2) % 300;
    lin.mm =  ((kletki * 1000) / 2) % 3000;

    return lin;
}