#include "image_view.hpp"

#include <QPainter>

ImageView::ImageView( QWidget* parent )
    : QWidget( parent )
{
    image = nullptr;
    backgroundColor = Qt::GlobalColor::transparent;
    aspectRatioMode = Qt::KeepAspectRatio;
    alignment = Qt::AlignCenter;
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

const QColor& ImageView::getBackgroungColor() const
{
    return backgroundColor;
}

Qt::AspectRatioMode ImageView::getAspectRatioMode() const
{
    return aspectRatioMode;
}

Qt::Alignment ImageView::getAlignment() const
{
    return alignment;
}

void ImageView::setBackgroundColor( const QColor& color )
{
    if( color != backgroundColor )
    {
        backgroundColor = color;
        this->repaint();
    }
}

void ImageView::setAspectRatioMode( Qt::AspectRatioMode mode )
{
    if( mode != aspectRatioMode )
    {
        aspectRatioMode = mode;
    }
}

void ImageView::setAlignment( Qt::Alignment alignment )
{
    if( this->alignment != alignment )
    {
        this->alignment = alignment;
    }
}

void ImageView::setImage( std::shared_ptr< QImage > image )
{
    this->image = image;
}

void ImageView::paintEvent( QPaintEvent* /*event*/ )
{
    QPainter painter( this );

    /// Draw background.
    painter.setPen( backgroundColor );
    painter.setBrush( backgroundColor );
    painter.drawRect( this->rect() );

    if( !image || image->isNull() ) return;

    /// Get scaled image.
    auto scaledImage =
        image->scaled( this->size(), aspectRatioMode );

    /// Get offsets.
    int x = 0, y = 0;
    if( alignment & Qt::AlignLeft )
        x = 0;
    else if( alignment & Qt::AlignRight )
        x = this->width() - scaledImage.width();
    else if( alignment & Qt::AlignHCenter )
        x = ( this->width() - scaledImage.width() ) / 2;
    if( alignment & Qt::AlignTop )
        y = 0;
    else if( alignment & Qt::AlignBottom )
        y = this->height() - scaledImage.height();
    else if( alignment & Qt::AlignVCenter )
        y = ( this->height() - scaledImage.height() ) / 2;

    /// Draw image.
    painter.drawImage( QPoint( x, y ), scaledImage );
}
