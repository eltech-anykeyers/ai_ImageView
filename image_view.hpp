#ifndef IMAGE_VIEW_HPP
#define IMAGE_VIEW_HPP

#include <QWidget>

#include <memory>

class ImageView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageView( QWidget* parent = Q_NULLPTR );
    explicit ImageView( std::shared_ptr< QImage > image,
                        QWidget* parent = Q_NULLPTR );
    ImageView( const ImageView& other );
    ImageView( ImageView&& other );
    virtual ~ImageView() override = default;

signals:

public slots:
    void setImage( std::shared_ptr< QImage > image );

protected:
    virtual void paintEvent( QPaintEvent* event ) override;

private:
    std::shared_ptr< QImage > image;

};

#endif /// IMAGE_VIEW_HPP
