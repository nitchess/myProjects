/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 13. 06. 18
* @dateLastModified : 22. 06. 18
* @brief            : translating cpp polymorphism to c 
*/ 

#include <stdio.h>
#include <stdlib.h>

/**
* Vtables & Vfunctions Declerations
**/
typedef struct Shape __Shape;

typedef void * (*func_t)(void *); // vTables func signature typedefs
typedef void  (*drawFunc)(__Shape *);
typedef void  (*scaleFunc)(__Shape *, double);
typedef void  (*dtorFunc)(__Shape *);

func_t __Scalable_vTable[2];
func_t __Shape_vTable[5];
func_t __Circle_vTable[5];
func_t __Rectangle_vTable[5];

/*
struct Color {
    enum ColorEnum { RED, GREEN, DEFAULT };
    static void setColor(ColorEnum color){      
        static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
        std::puts(pallete[color]);
    }
};
*/
typedef enum __Color__ColorEnum {RED, GREEN, DEFAULT} __Color__ColorEnum; // Struct members are public by default
typedef struct Color
{
    char c; // empty struct size in c++ is 1 byte
}__Color;

// Static functions in c++ does not take an object - in a struct they are public by default.
void __Color__enum__setColor(__Color__ColorEnum _color)
{       
    static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
    puts(pallete[_color]);

    return;
}

/*
class Scaleable {
public:
    virtual ~Scaleable() { }    
    virtual void scale(double) = 0;
};
*/
typedef struct Scaleable
{
    func_t *   m_vTable;

}__Scaleable;

void __Scaleable_V_DTOR(__Scaleable* _this){}
void __Scaleable_V_Scale_1d(double f){}

func_t __Scalable_vTable[2] = {     (func_t)__Scaleable_V_DTOR, 
                                    (func_t)__Scaleable_V_Scale_1d };

void __Scaleable__CTOR(__Scaleable* _this)
{
    _this->m_vTable = __Scalable_vTable;
}

// COPY CTOR + Assigment CTOR



/*
Class Shape
{
private:
    static int NumOfShapes;
    Shape& operator=(const Shape &); // disabled, no implementation provided

protected:
     int m_id;
};

int Shape::NumOfShapes = 0;
*/
struct Shape
{
    __Scaleable     m_baseClass;
    int             m_id; //protected

};

int __Shape_NumOfShapes = 0; // static member

/*
class Shape : public Scaleable {
public:
    Shape() : m_id(++NumOfShapes) {
        std::printf("Shape::Shape() - %d\n", m_id); 
    }
*/
void __Shape_CTOR(__Shape * const _this)
{
    __Scaleable__CTOR((__Scaleable *)_this);
    _this->m_baseClass.m_vTable = __Shape_vTable;

    _this->m_id = ++__Shape_NumOfShapes;
    printf("Shape::Shape() - %d\n", _this->m_id);

    return;
}


/*
    Shape(const Shape& other) : m_id(++NumOfShapes) {
        std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);
    }
*/
void __Shape_Copy_CTOR(__Shape * const _to, const __Shape * const _from)
{   
    __Scaleable__CTOR((__Scaleable *)_to);
    _to->m_baseClass.m_vTable = __Shape_vTable;
    _to->m_id = ++__Shape_NumOfShapes;

    printf("Shape::Shape(Shape&) - %d from - %d\n", _to->m_id, _from->m_id);
   
   return; 
}


/* virtual void draw() const 
{
    std::printf("Shape::draw() - %d\n", m_id);      
}
*/
void __Shape_V_Draw(const __Shape * const _this)
{
    printf("Shape::draw() - %d\n", _this->m_id);

    return;
}

/*
    ~Shape() {
        draw();
        --NumOfShapes; 
        std::printf("Shape::~Shape - %d\n", m_id);
    }
*/
void __Shape_V_DTOR(__Shape * _this)
{
    __Shape_V_Draw(_this);
    __Shape_NumOfShapes--;
    printf("Shape::~Shape - %d\n", _this->m_id);    

    return;
}

/*    
    virtual void draw(Color::ColorEnum c) const {
        std::printf("Shape::draw(c) - %d\n", m_id);
        Color::setColor(c);
        draw();
        Color::setColor(Color::DEFAULT);
    }
*/
void __Shape_V_Draw_1enum(const __Shape * const _this, __Color__ColorEnum _color)
{
    printf("Shape::draw(c) - %d\n", _this->m_id);

    __Color__enum__setColor(_color);
    __Shape_V_Draw(_this);
    __Color__enum__setColor(DEFAULT);

    return;
}

/*
    virtual void scale(double f = 1) { 
        std::printf("Shape::scale(%f)\n", f);
    }
*/
void __Shape_V_Scale_1d(double f)
{
    printf("Shape::scale(%f)\n", f);

    return;
}

/*  
    virtual double area() const { return -1; }
*/
double __Shape_V_Area(const __Shape * const _this)
{
    return -1;
}

/*
    static void printInventory() {
        std::printf("Shape::printInventory - %d\n", NumOfShapes);
    }
*/
void __Shape_PrintInventory()
{
   printf("Shape::printInventory - %d\n", __Shape_NumOfShapes);
   
   return; 
}


func_t __Shape_vTable[5] = {      (func_t)__Shape_V_DTOR 
                                , (func_t)__Shape_V_Draw
                                , (func_t)__Shape_V_Draw_1enum
                                , (func_t)__Shape_V_Scale_1d
                                , (func_t)__Shape_V_Area
                                };


/*class Circle : public Shape 
{  
private:
    double m_radius;
*/
typedef struct Circle
{
    __Shape     m_baseClass;
    double      m_radius;

}__Circle;

/* 
public:
Circle() : m_radius(1) { 
    std::printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); 
}
*/
void __Circle_CTOR(__Circle * const _this)
{
    __Shape_CTOR((__Shape*)_this);
    _this->m_baseClass.m_baseClass.m_vTable = __Circle_vTable;

    _this->m_radius = 1;
    printf("Circle::Circle() - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);

    return;
}

/*
Circle(double r) : m_radius(r) { 
    std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
}
*/
void __Circle_CTOR_1d(__Circle * const _this, double _r)
{
    __Shape_CTOR((__Shape*)_this);
    _this->m_baseClass.m_baseClass.m_vTable = __Circle_vTable;

    _this->m_radius = _r;
    printf("Circle::Circle(double) - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);

    return;
}

/*
Circle(const Circle& other)
: Shape(other), m_radius(other.m_radius) { 
    std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
}
*/
void __Circle_C_CTOR(__Circle * const _this, const __Circle * const _other)
{
    __Shape_Copy_CTOR((__Shape*)_this, (__Shape*)_other);
    _this->m_baseClass.m_baseClass.m_vTable = __Circle_vTable;

    _this->m_radius = _other->m_radius;
    printf("Circle::Circle(Circle&) - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);

    return;
}

/*
~Circle() { 
    std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
}
*/
void __Circle_V_DTOR(__Circle * const _this)
{
    printf("Circle::~Circle() - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);

    __Shape_V_DTOR((__Shape *) _this);
    return;
}

/*
void draw() const { 
    std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
}
*/
void __Circle_V_Draw(const __Circle * const _this)
{
    printf("Circle::draw()  - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);

    return;
}

/*
void scale(double f = 2) {
    std::printf("Circle::scale(%f)\n", f);
    m_radius *= f;
}
*/
void __Circle_V_Scale_1d(__Circle * const _this, double f)
{
    printf("Circle::scale(%f)\n", f);

    _this->m_radius *= f;

    return;
}

/*
double area() const {
    return m_radius * m_radius * 3.1415;    
}
*/
double __Circle_V_Area(const __Circle * const _this)
{
    return (_this->m_radius * _this->m_radius * 3.1415);
}

/*
double radius() const { 
    std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
    return m_radius;
}
*/
double __Circle_Radius(const __Circle * const _this)
{
    printf("Circle::draw()  - %d, r:%f\n", _this->m_baseClass.m_id, _this->m_radius);
    return (_this->m_radius);
}

func_t __Circle_vTable[5] = {    (func_t)__Circle_V_DTOR, 
                                 (func_t)__Circle_V_Draw,
                                 (func_t)__Shape_V_Draw_1enum,
                                 (func_t)__Circle_V_Scale_1d,
                                 (func_t)__Circle_V_Area
                                };

/*
class Rectangle: public Shape {
private:
    int m_a, m_b;
};
*/
typedef struct Rectangle
{   
    __Shape m_baseClass;
    int     m_a;
    int     m_b;
}__Rectangle;

/*
Rectangle() : m_a(1), m_b(1) 
{ 
        std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
}
*/
void __Rectangle_D_CTOR(__Rectangle * const _this)
{
    __Shape_CTOR((__Shape*)_this);
    _this->m_baseClass.m_baseClass.m_vTable = __Rectangle_vTable;

    _this->m_a = 1;
    _this->m_b = 1;

    printf("Rectangle::Rectangle() - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);

    return;
}

/*
Rectangle(int a) : m_a(a), m_b(a)
{ 
        std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
}
*/
void __Rectangle_CTOR_1d(__Rectangle * const _this, double a)
{
    __Shape_CTOR((__Shape*)_this);
    _this->m_baseClass.m_baseClass.m_vTable = __Rectangle_vTable;

    _this->m_a = a;
    _this->m_b = a;

    printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);

    return;
}

/*
Rectangle(int a, int b) : m_a(a), m_b(b)
{ 
        std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
}
*/
void __Rectangle_CTOR_2d(__Rectangle * const _this, double a, double b)
{
    __Shape_CTOR((__Shape*)_this);
    _this->m_baseClass.m_baseClass.m_vTable = __Rectangle_vTable;

    _this->m_a = a;
    _this->m_b = b;

    printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);

    return;
}

/*
Rectangle(const Rectangle &other ) 
    : m_a(other.m_a), m_b(other.m_b), Shape(other) 
{ 
        std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
*/
void __Rectangle_C_CTOR(__Rectangle * const _this, const __Rectangle * const _other)
{
    __Shape_Copy_CTOR((__Shape*)_this, (__Shape*)_other);
    _this->m_baseClass.m_baseClass.m_vTable = __Rectangle_vTable;

    _this->m_a = _other->m_a;
    _this->m_b = _other->m_b;

    printf("Rectangle::Rectangle(Rectangle&) - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);

    return;
}

/*
~Rectangle() 
{ 
        std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
}
*/
void __Rectangle_V_DTOR(const __Rectangle * const _this)
{
    printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);
    __Shape_V_DTOR((__Shape *) _this);

    return;
}

/*
void draw() const 
{ 
        std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
}
*/
void __Rectangle_V_Draw(const __Rectangle * const _this)
{
    printf("Rectangle::draw()  - %d, [%d, %d]\n", _this->m_baseClass.m_id, _this->m_a, _this->m_b);
    return;
}

/*
void draw(Color::ColorEnum c) const
{
        std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
}
*/
void __Rectangle_V_Draw_1st(__Rectangle * _this, __Color__ColorEnum c)
{
    printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, _this->m_baseClass.m_id, _this->m_a, _this->m_b);
    return;
}

/*void scale(double f = 4){
        std::printf("Rectangle::scale(%f)\n", f);
        m_a *= f;
        m_b *= f;
    }*/
void __Rectangle_V_Scale_1d(__Rectangle * _this, double f)
{
    printf("Rectangle::scale(%f)\n", f);

    _this->m_a *= f;
    _this->m_b *= f; 

    return;
}

/*
    double area() const {
        return m_a * m_b;
    }
*/
double __Rectangle_V_Area(const __Rectangle * const _this)
{
    return (_this->m_a * _this->m_b);
}

func_t __Rectangle_vTable[5] = {      (func_t)__Rectangle_V_DTOR
                                , (func_t)__Rectangle_V_Draw
                                , (func_t)__Rectangle_V_Draw_1st
                                , (func_t)__Rectangle_V_Scale_1d
                                , (func_t)__Rectangle_V_Area
                                };

/*
void report(const Shape& s) {
    std::puts("-----report-----");
    s.draw(); 
    Shape::printInventory();
    std::puts("-----report-----");
}
*/
void __Report_1ShapePtr(const __Shape * const s)
{
    puts("-----report-----");
    ((drawFunc)s->m_baseClass.m_vTable[1])( (__Shape*)s );
    __Shape_PrintInventory();
    puts("-----report-----");

    return;
}

/*
inline void draw(Shape& obj) { 
    std::puts("-----draw(Shape&)-----");
    obj.scale();
    obj.draw();
    
    static Circle unit(4);
    
    std::puts("-----draw(Shape&)-----");
}
*/
// Static for 1 creation point & Global for DTOR in end of main
__Circle unit;
int flagFirstdraw=0;
// 
void __Inline__Draw__1ShapePtr(__Shape * const obj)
{
    puts("-----draw(Shape&)-----");
    ((scaleFunc)obj->m_baseClass.m_vTable[3])( (__Shape*)obj, 1.0 );
    ((drawFunc)obj->m_baseClass.m_vTable[1])( (__Shape*)obj );

    if (flagFirstdraw == 0)
    {
        __Circle_CTOR_1d(&unit, 4);
        flagFirstdraw = 1;
    }

    puts("-----draw(Shape&)-----");

    return;
}

/*
void draw(Circle c) { 
    std::puts("-----draw(Circle)-----");

    if(c.area() > 3.14){
        static Circle unit(1);
        unit.draw();
        unit.scale(3);
    }
    
    c.draw(); 
    std::puts("-----draw(Circle)-----");
}
*/
__Circle unit1;
int flag_2_Firstdraw=0;
void __Draw__1CircleObj(__Circle c)
{
    __Circle cc;
    __Circle_C_CTOR(&cc, &c);

    puts("-----draw(Circle)-----");

    if(__Circle_V_Area(&c) > 3.14)
    {
        if (flag_2_Firstdraw == 0)
            {
                __Circle_CTOR_1d(&unit1, 1);
                
                flag_2_Firstdraw = 1;
            }

        __Circle_V_Draw(&unit1);
        __Circle_V_Scale_1d(&unit1, 3.0);
    }

    __Circle_V_Draw(&cc);
    puts("-----draw(Circle)-----");

    __Circle_V_DTOR(&cc);
    return;
}

/*
void doObjArray(){
    Shape objects[] = {
        Circle(),
        Rectangle(4),
        Circle(9)
    };

    for(int i = 0; i < 3; ++i) 
        objects[i].draw();
}
*/
void __do_Obj_Array()
{
    int i;
    __Shape objects[3];
    __Circle c1_temp, c2_temp;
    __Rectangle r1_temp;

    // Init
    __Circle_CTOR(&c1_temp);
    __Shape_Copy_CTOR(&objects[0], (__Shape*)&c1_temp);

    __Rectangle_CTOR_1d(&r1_temp, 4);
    __Shape_Copy_CTOR(&objects[1], (__Shape*)&r1_temp);

    __Circle_CTOR_1d(&c2_temp, 9);    
    __Shape_Copy_CTOR(&objects[2], (__Shape*)&c2_temp);

    __Circle_V_DTOR(&c2_temp);
    __Rectangle_V_DTOR(&r1_temp);
    __Circle_V_DTOR(&c1_temp);

    for (int i = 0; i < 3; ++i)
    {
        ((drawFunc)objects[i].m_baseClass.m_vTable[1])(&objects[i]);
    }
    for (int i = 2; i >= 0; --i)
    {
        ((drawFunc)objects[i].m_baseClass.m_vTable[0])(&objects[i]);
    }

    return;
}

 
void disappear() {
    puts("-----disappear-----");

    // Function Decleration
    __Circle defaultCircle();

    puts("-----disappear-----");
}

/*
template <class T>
double diffWhenDoubled(T& shape){
    double a0 = shape.area();
    shape.scale(2);
    double a1 = shape.area();
    return a1 - a0;
}
*/
double __Circle_dif_when_doubled(__Circle * const shape)
{
    double a0 = __Circle_V_Area(shape);
    __Circle_V_Scale_1d(shape, 2);
    double a1 = __Circle_V_Area(shape);
    return (a1 - a0);
}

double __Rectangle_dif_when_doubled(__Rectangle * const shape)
{
    double a0 = __Rectangle_V_Area(shape);
    __Rectangle_V_Scale_1d(shape, 2);
    double a1 = __Rectangle_V_Area(shape);
    return (a1 - a0);
}

/*void doPointerArray(){
    std::puts("-----doPointerArray-----");
    Shape *array[] =  {
        new Circle(),
        new Rectangle(3),
        new Circle(4)
    };

    for(int i = 0; i < 3; ++i){ 
        array[i]->scale();
        array[i]->draw();
    }

    std::printf("area: %f\n", diffWhenDoubled(*array[2]));

    for(int i = 0; i < 3; ++i) { 
        delete array[i]; 
        array[i] = 0; 
    }

    std::puts("-----doPointerArray-----");
}*/
void __Do_Pointer_Array()
{
    int i;
    __Shape * array[3];
   puts("-----doPointerArray-----");

    __Circle * c1_tmp; 
    c1_tmp = (__Circle*)malloc(sizeof(__Circle));
    __Circle_CTOR(c1_tmp);

    __Rectangle* r_tmp; 
    r_tmp = (__Rectangle*)malloc(sizeof(__Rectangle));
    __Rectangle_CTOR_1d(r_tmp, 3);

    __Circle* c2_tmp; 
    c2_tmp = (__Circle*)malloc(sizeof(__Circle));
    __Circle_CTOR_1d(c2_tmp, 4);

    array[0] = (__Shape*)c1_tmp;
        array[1] = (__Shape*)r_tmp;
            array[2] = (__Shape*)c2_tmp;

    for (i = 0; i < 3; ++i)
    {
        // scale()
        ((scaleFunc)array[i]->m_baseClass.m_vTable[3])(array[i], 1); 
        // draw()
        ((drawFunc)array[i]->m_baseClass.m_vTable[1])(array[i]); 
    }

    printf("area: %f\n", __Circle_dif_when_doubled((__Circle*)array[2]));

    for (i = 0; i < 3; ++i)
    {
        ((drawFunc)array[i]->m_baseClass.m_vTable[0])(array[i]); 
    }
    
    puts("-----doPointerArray-----");
    return; 
}

int main(int argc, char **argv, char **envp)
{   
    // Initializations:
    int i;
    __Circle c, c2;
    __Circle olympics[5];
    __Rectangle s;

    printf("---------------Start----------------\n");
    // Static Function member init

    // Circle c;
    __Circle_CTOR(&c);
    // Rectangle s(4);
    __Rectangle_CTOR_1d(&s, 4);
    printf("0.-------------------------------\n"); 
    
    // copy CTOR will be called 
    // static binding to circle object   
    // draw(c);
    __Draw__1CircleObj(c);
    printf("+..............\n");
    
    // draw(c);
    __Draw__1CircleObj(c);
    printf("+..............\n");
    
    // draw(s)
    // No static binding, pass by ref/ptr 
    __Inline__Draw__1ShapePtr((__Shape*)&s);
    printf("+..............\n");       
    
    // report(c);
    __Report_1ShapePtr((__Shape*)&c);
    printf("1.-------------------------------\n"); 
    
    // doPointerArray();
    __Do_Pointer_Array();

    printf("2.-------------------------------\n");

    // doObjArray();
    __do_Obj_Array();

    printf("3.-------------------------------\n");

    // Shape::printInventory();
    __Shape_PrintInventory();
    // Circle c2 = c;
    __Circle_C_CTOR(&c2, &c);
    // c2.printInventory();
    __Shape_PrintInventory();

    printf("4.-------------------------------\n");
   
    for (i = 0; i < 5; ++i)
    {
        __Circle_CTOR(&olympics[i]);
    }
    printf("olympic diff %f\n", __Circle_dif_when_doubled(&olympics[1]));

    printf("5.-------------------------------\n");

    /*
    Rectangle *fourRectangles = new Rectangle[4];
    dispose(fourRectangles);

    std::printf("6.-------------------------------\n");
    EmptyBag eb;
    std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );
    
    std::printf("7.-------------------------------\n");
    disappear();    

    std::printf("---------------END----------------\n");
    */

    return 0;
}

/*
typedef union
{
    __Circle c;
    __Rectangle r;

}__Shape_union;

void __do_Obj_Array()
{   
    int i;
    __Circle c1, c2;
    __Rectangle r1;

    // Init
    __Circle_CTOR(&c1);


    __Rectangle_CTOR_1d(&r1, 4);


    __Circle_CTOR_1d(&c2, 9);

    // __Shape_union s1 = {.r = r1};
    __Shape_union objects[3] = {
                                        { .c = c1 }
                                    ,   { .r = r1 }
                                    ,   { .c = c2 }
                                };


    // draw

    for (i = 0; i < 3; ++i)
    {   

        ((drawFunc)((__Shape*)&objects[i])->m_baseClass.m_vTable[1])( (__Shape*)&objects[i] );
        ((drawFunc)((__Shape*)&objects[i])->m_baseClass.m_vTable[0])( (__Shape*)&objects[i] );
    }
   

    return;
}*/

/*
__Shape * __NewShape(Rectangle * p, size_t n)
{
    int i;
    int alignment;

    typedef struct
    {
        char c;
        union
        {
            char cc;
            short s;

        };

    }__s;
    
    p = (Rectangle*)malloc(sizeof(size_t) + n * sizeof(Rectangle));
    *(size_t*)p = n;

    for (i = 1; i < n+1; ++i)
    {
        // __Rectangle_D_CTOR(p[i]);
    }

    return (p + 1);
}

void _Rectangle_FreeArray(Rectangle * p)
{
    int i;
    // int size = (int)p[0];
    // free (p - );

}
*/
