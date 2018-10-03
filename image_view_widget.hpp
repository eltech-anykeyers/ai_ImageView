#ifndef IMAGE_VIEW_HPP
#define IMAGE_VIEW_HPP

#include <QWidget>

#include <memory>

class ImageViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewWidget( QWidget* parent = Q_NULLPTR );
    explicit ImageViewWidget( std::shared_ptr< QImage > image,
                        QWidget* parent = Q_NULLPTR );
    ImageViewWidget( const ImageViewWidget& other );
    ImageViewWidget( ImageViewWidget&& other );
    virtual ~ImageViewWidget() override = default;

    const QColor& getBackgroungColor() const;
    Qt::AspectRatioMode getAspectRatioMode() const;
    Qt::Alignment getAlignment() const;

signals:

public slots:
    void setBackgroundColor( const QColor& color );
    void setAspectRatioMode( Qt::AspectRatioMode mode );
    void setAlignment( Qt::Alignment alignment );
    void setImage( std::shared_ptr< QImage > image );

protected:
    virtual void paintEvent( QPaintEvent* event ) override;

private:
    std::shared_ptr< QImage > image;
    QColor backgroundColor;
    Qt::AspectRatioMode aspectRatioMode;
    Qt::Alignment alignment;
};

#endif /// IMAGE_VIEW_HPP
