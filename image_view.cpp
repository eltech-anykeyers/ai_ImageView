#include "image_view.hpp"

#include <QPainter>

ImageView::ImageView( QWidget* parent )
    : QWidget( parent )
{
    image = nullptr;
}

ImageView::ImageView(
    std::shared_ptr< QImage > image, QWidget* parent )
    : ImageView( parent )
{
    this->setImage( image );
    this->repaint();
}

ImageView::ImageView( const ImageView& other )
    : ImageView( other.image )
{}

ImageView::ImageView( ImageView&& other )
    : ImageView( other.image )
{}

void ImageView::setImage( std::shared_ptr< QImage > image )
{
    this->image = image;
}

void ImageView::paintEvent( QPaintEvent* /*event*/ )
{
    QPainter painter( this );

    if( !image || image->isNull() )
    {
       return;
    }

    painter.drawImage( QPoint( 0, 0 ), *image );
}
