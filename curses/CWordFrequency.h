#ifndef CWORDFREQUENCY_H_INCLUDED
#define CWORDFREQUENCY_H_INCLUDED

class CWordFrequency
{

   private:
       int countBeginning;
       int countEnd;
       int countWithin;

   public:
       CWordFrequency();
       ~CWordFrequency();
       void incrementCountBeginning();
       void incrementCountEnd();
       void incrementCountWithin();
       int returnCountBeginning();
       int returnCountEnd();
       int returnCountWithin();

};

#endif // CWORDFREQUENCY_H_INCLUDED
