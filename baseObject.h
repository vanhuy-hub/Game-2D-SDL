


#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include"commonfunc.h"

class baseObject {
public :
    baseObject();
    ~baseObject();//ham huy
    void SetRect(const int &x,const int &y){ rect_.x=x;rect_.y=y;}
      void SetRect(const SDL_Rect& rect) { rect_ = rect; } // Thêm hàm SetRect nhận SDL_Rect
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject()const {return p_object_; }
    void SetTexture(SDL_Texture* texture); // Thêm hàm setTexture
    SDL_Texture* GetTexture(); // Thêm hàm getTexture
   virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Render (SDL_Renderer* des,const SDL_Rect* clip=NULL);
    void Free();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;


};


#endif // BASE_OBJECT_H_
