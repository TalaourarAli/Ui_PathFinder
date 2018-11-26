#include <QLabel>

class Clickable :public QLabel
    {
        Q_OBJECT
            signals :
        void clicked();
    public:
        void mousePressEvent(QMouseEvent* event);

        using QLabel::QLabel;
        ~Clickable(){
            delete this;
        }
    };
