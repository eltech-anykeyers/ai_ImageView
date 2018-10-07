#include "image_view_widget.hpp"

#include <QPainter>

ImageViewWidget::ImageViewWidget( QWidget* parent )
    : QWidget( parent )
{
    image = nullptr;
    backgroundColor = Qt::GlobalColor::transparent;
    aspectRatioMode = Qt::KeepAspectRatio;
    alignment = Qt::AlignCenter;
}

ImageViewWidget::ImageViewWidget(
    std::shared_ptr< QImage > image, QWidget* parent )
    : ImageViewWidget( parent )
{
    this->setImage( image );
    this->repaint();
}

ImageViewWidget::ImageViewWidget( const ImageViewWidget& other )
    : ImageViewWidget( other.image )
{}

ImageViewWidget::ImageViewWidget( ImageViewWidget&& other )
    : ImageViewWidget( other.image )
{}

const QColor& ImageViewWidget::getBackgroungColor() const
{
    return backgroundColor;
}

Qt::AspectRatioMode ImageViewWidget::getAspectRatioMode() const
{
    return aspectRatioMode;
}

Qt::Alignment ImageViewWidget::getAlignment() const
{
    return alignment;
}

void ImageViewWidget::setBackgroundColor( const QColor& color )
{
    if( color != backgroundColor )
    {
        backgroundColor = color;
        this->repaint();
    }
}

void ImageViewWidget::setAspectRatioMode( Qt::AspectRatioMode mode )
{
    if( mode != aspectRatioMode )
    {
        aspectRatioMode = mode;
    }
}

void ImageViewWidget::setAlignment( Qt::Alignment alignment )
{
    if( this->alignment != alignment )
    {
        this->alignment = alignment;
    }
}

void ImageViewWidget::setImage( std::shared_ptr< QImage > image )
{
    this->image = image;
}

void ImageViewWidget::paintEvent( QPaintEvent* /*event*/ )
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

    /// Compute offsets.
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
