#ifndef MISC_H
#define MISC_H

class Validate
{
    public:
        Validate() {}
        virtual ~Validate() {}
        virtual void validate() const = 0;

};

#endif // MISC_H
