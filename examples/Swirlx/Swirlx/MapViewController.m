//
//  MapViewController.m
//  Swirl
//
//  Created by Thomas Middleton on 8/11/16.
//
//
#import <Swirl/Swirl.h>
#import <MapKit/MapKit.h>
#import "MapViewController.h"

#define FILTER_ALL      0
#define FILTER_GEO      1
#define FILTER_CONTROL  2

@interface MapViewController () <MKMapViewDelegate, UITableViewDelegate, UITableViewDataSource,
                                 SWRLSwirlDelegate, SWRLRegionManagerDelegate>

@property (nonatomic) MKMapView *mapView;
@property (nonatomic) UILabel *separatorView;
@property (nonatomic) UIPanGestureRecognizer *separatorDrag;
@property (nonatomic) UITableView *tableView;
@property (nonatomic) UISegmentedControl *filter;
@property (nonatomic) NSMutableDictionary<NSValue*,SWRLRegion*> *regionForOverlay;
@property (nonatomic) MKPointAnnotation *sdkLocation;
@property (nonatomic) NSMutableArray<MKPointAnnotation *> *locationHistory;
@end

@implementation MapViewController

- (int) filterValue {
    return (int)_filter.selectedSegmentIndex;
}

// =====================================================================================================================
#pragma mark SWIRL DELEGATES
// =====================================================================================================================

- (void) updateOverlaysAndAnnotations {
    [_mapView removeOverlays:_mapView.overlays];
    [_mapView removeAnnotations:_mapView.annotations];

    for (MKPointAnnotation *annotation in _locationHistory) {
        // since sdkLocation provides a pin for current location, skip the first history entry
        if (annotation != _locationHistory.firstObject)
            [_mapView addAnnotation:annotation];
    }
    [_mapView addAnnotation:_sdkLocation];
    [self addOverlayForRegion:[SWRLRegionManager shared].monitoredArea];
    for (SWRLRegion *region in [SWRLRegionManager shared].monitoredRegions) {
        if ( self.filterValue == FILTER_ALL ||
            (self.filterValue == FILTER_GEO     && region.location != nil) ||
            (self.filterValue == FILTER_CONTROL && region.location == nil)) {
            [self addOverlayForRegion:region];
        }
    }
}

- (MKPointAnnotation *)annotationForLocation:(CLLocation *)location {
    MKPointAnnotation *annotation = [MKPointAnnotation new];
    annotation.coordinate = location.coordinate;
    NSDateFormatter *formatter = [NSDateFormatter new];
    formatter.dateStyle = NSDateFormatterShortStyle;
    formatter.timeStyle = NSDateFormatterMediumStyle;
    annotation.title = [NSString stringWithFormat:@"%.3f,%.3f @ %@",
            location.coordinate.latitude, location.coordinate.longitude,
            [formatter stringFromDate:location.timestamp]];
    annotation.subtitle = location.description;
    return annotation;
}

- (void) addHistoryAnnotation:(CLLocation *)location {
    if (location) {
        [_locationHistory insertObject:[self annotationForLocation:location] atIndex:0];
        [_tableView reloadData];
    }
}

- (void) showAnnotation:(id<MKAnnotation>)annotation select:(BOOL)select {
    if (annotation == _locationHistory.firstObject)
        annotation = _sdkLocation;
    [UIView animateWithDuration:0.25 animations:^{
        _mapView.centerCoordinate = annotation.coordinate;
        if (select) [_mapView selectAnnotation:annotation animated:NO];
    }];
}

- (void) swirlDidUpdateLocation:(CLLocation *)location {
    [self addHistoryAnnotation:location];
    _sdkLocation = [self annotationForLocation:location];
    [UIView animateWithDuration:0.25 animations:^{
        _mapView.centerCoordinate = location.coordinate;
        [self updateOverlaysAndAnnotations];
    }];
}

- (void) regionManager:(SWRLRegionManager *)manager didEnterRegions:(NSSet<SWRLRegion *> *)entered exitRegions:(NSSet<SWRLRegion *> *)exited {
    [self updateOverlaysAndAnnotations];
}

// =====================================================================================================================
#pragma mark - MAPVIEW DELEGATES
// =====================================================================================================================

- (void) addOverlayForRegion:(SWRLRegion *)region {
    MKCircle *overlay = [MKCircle circleWithCenterCoordinate:region.region.center radius:region.region.radius];
    
    if ([region isEqual:[SWRLRegionManager shared].monitoredArea]) {
        overlay.title = @"monitoredArea";
        overlay.subtitle = region.description;
    } else if (region.location) {
        overlay.title = region.location.name;
        overlay.subtitle = region.location.description;
    } else {
        overlay.title = @"control";
        overlay.subtitle = region.description;
    }
    
    _regionForOverlay[[NSValue valueWithNonretainedObject:overlay]] = region;
    [_mapView addAnnotation:overlay];
    [_mapView addOverlay:overlay];
    if (region.polyCount > 0) {
        MKPolygon *polygon = [MKPolygon polygonWithCoordinates:region.polyCoords count:region.polyCount];
        _regionForOverlay[[NSValue valueWithNonretainedObject:polygon]] = region;
        [_mapView addOverlay:polygon];
    }
}

- (SWRLRegion *)regionForOverlay:(id<MKOverlay>)overlay {
    return _regionForOverlay[[NSValue valueWithNonretainedObject:overlay]];
}

- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id<MKOverlay>)overlay {
    SWRLRegion *            region      = [self regionForOverlay:overlay];
    MKOverlayPathRenderer * renderer    = [overlay isKindOfClass:[MKCircle class]] ? [[MKCircleRenderer alloc] initWithCircle:overlay] :
                                                [[MKPolygonRenderer alloc] initWithPolygon:overlay];
    
    renderer.lineWidth = 1;
    if ([region isEqual:[SWRLRegionManager shared].monitoredArea]) {
        renderer.strokeColor = [UIColor blackColor];
        renderer.lineWidth = 2;
        //renderer.lineDashPattern = @[@3,@8];
    } else if ([[SWRLRegionManager shared].enteredRegions containsObject:region]) {
        //NSLog(@"in-region: %@ (%@)", region, region.info);
        renderer.strokeColor = [UIColor redColor];
        renderer.lineWidth = 2;
        renderer.fillColor = region.polyCount == 0 ? [UIColor colorWithRed:1.0 green:0 blue:0 alpha:.01] : [UIColor clearColor];
    } else if ([region.regionType isEqualToString:@"geofence"]) {
        renderer.strokeColor = [UIColor greenColor];
        renderer.fillColor = region.polyCount == 0 ? [UIColor colorWithRed:0 green:1.0 blue:0 alpha:.01] : [UIColor clearColor];
    } else {
        CGFloat r,g,b,a;
        renderer.strokeColor = [MKPinAnnotationView purplePinColor];
        [[MKPinAnnotationView purplePinColor] getRed:&r green:&g blue:&b alpha:&a];
        renderer.fillColor = [UIColor colorWithRed:r green:g blue:b alpha:0.01];
    }
    
    // if this is the outer-circle for a polygon region, draw it with a dash
    if ([overlay isKindOfClass:[MKCircle class]] && region.polyCount > 0)
        renderer.lineDashPattern = @[@4, @8];
        
    return renderer;
}

- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation {
    if (annotation == mapView.userLocation)
        return nil;
    
    MKPinAnnotationView *pinView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:nil];
    if (annotation == _sdkLocation) {
        pinView.pinTintColor = [UIColor blueColor];
        pinView.draggable = YES;
    } else if ([_locationHistory containsObject:annotation]) {
        pinView.pinTintColor = [UIColor orangeColor];
    } else {
        SWRLRegion *region = [self regionForOverlay:(id)annotation];
        if ([region isEqual:[SWRLRegionManager shared].monitoredArea]) {
            pinView.pinTintColor = [UIColor blackColor];
        } else if ([[SWRLRegionManager shared].enteredRegions containsObject:region]) {
            pinView.pinTintColor = [UIColor redColor];
        } else if ([region.regionType isEqualToString:@"geofence"]) {
            pinView.pinTintColor = [MKPinAnnotationView greenPinColor];
        } else {
            pinView.pinTintColor = [MKPinAnnotationView purplePinColor];
        }
    }
    pinView.canShowCallout = YES;
    return pinView;
}

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)annotationView didChangeDragState:(MKAnnotationViewDragState)state
   fromOldState:(MKAnnotationViewDragState)prevState {
    if (state == MKAnnotationViewDragStateEnding) {
        CLLocationCoordinate2D coord = annotationView.annotation.coordinate;
        [[Swirl shared] postObject:[[CLLocation alloc] initWithLatitude:coord.latitude
                                                              longitude:coord.longitude]];
    }
}

// =====================================================================================================================
#pragma mark - TABLEVIEW DELEGATES
// =====================================================================================================================

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _locationHistory.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"default"];
    if (cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"default"];
    MKPointAnnotation *historyAnnotation = _locationHistory[indexPath.row];
    cell.textLabel.font = [UIFont systemFontOfSize:14.0];
    cell.textLabel.text = historyAnnotation.title;
    cell.textLabel.textColor = [UIColor blackColor];
    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self showAnnotation:_locationHistory[indexPath.row] select:YES];
}

// =====================================================================================================================
#pragma mark - ACTIONS
// =====================================================================================================================

- (void) layoutSubviews:(CGFloat)separatorPos {
    CGRect frame;
    
    frame = self.view.frame; frame.size.height = separatorPos;
    _mapView.frame = frame;
    
    frame = _separatorView.frame; frame.origin.y = separatorPos;
    _separatorView.frame = frame;
    
    frame = CGRectMake(0, CGRectGetMaxY(_separatorView.frame), CGRectGetWidth(self.view.frame),
                       CGRectGetHeight(self.view.frame)-separatorPos);
    _tableView.frame = frame;
}

- (void) filterChanged:(id)unused {
    [self updateOverlaysAndAnnotations];
}

- (void) showUser:(id)unsued {
    [self showAnnotation:_sdkLocation select:YES];
}

- (void) didDrag:(UIPanGestureRecognizer *)pan {
    switch (pan.state) {
        case UIGestureRecognizerStateChanged: {
            [self layoutSubviews:[pan locationInView:self.view].y];
            break;
        }
        case UIGestureRecognizerStateEnded: {
            break;
        }
        default: break;
    }
}

// =====================================================================================================================
#pragma mark - INIT / DEALLOC
// =====================================================================================================================

- (void) dealloc {
    [[Swirl shared] removeDelegate:self];
}

- (instancetype)init {
    if ((self = [super init]) != nil) {
        _regionForOverlay = [NSMutableDictionary new];
        _locationHistory = [NSMutableArray new];
        
        _filter = [[UISegmentedControl alloc] initWithItems:@[@"All",@"Geo",@"Control"]];
        [_filter addTarget:self action:@selector(filterChanged:) forControlEvents:UIControlEventValueChanged];
        [_filter sizeToFit];
        [_filter setSelectedSegmentIndex:FILTER_GEO];
        
        self.navigationItem.titleView = _filter;
        
        
        // setup show current
        self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemSearch target:self action:@selector(showUser:)];
        
        // initialize this view
        self.view.autoresizingMask = UIViewAutoresizingNone;
        self.view.autoresizesSubviews = NO;
        
        // initialize the map view
        CGRect mapFrame = self.view.frame;
        mapFrame.size.height -= 200;
        
        _mapView = [[MKMapView alloc] initWithFrame:mapFrame];
        _mapView.autoresizingMask = UIViewAutoresizingNone;
        _mapView.delegate = self;
        _mapView.showsScale = YES;
        _mapView.showsUserLocation = YES;
        _mapView.centerCoordinate = _mapView.userLocation.coordinate;
        _mapView.region = MKCoordinateRegionMakeWithDistance([SWRLRegionManager shared].monitoredArea.region.center,
                                                             [SWRLRegionManager shared].monitoredArea.region.radius,
                                                             [SWRLRegionManager shared].monitoredArea.region.radius);
        [_mapView removeConstraints:_mapView.constraints];
        [self.view addSubview:_mapView];
        
        CGRect separatorFrame = self.view.frame;
        separatorFrame.origin.y = CGRectGetHeight(mapFrame);
        separatorFrame.size.height = 15;
        separatorFrame = CGRectInset(separatorFrame, -1, 0);
        _separatorView = [[UILabel alloc] initWithFrame:separatorFrame];
        _separatorView.backgroundColor = [UIColor colorWithWhite:.95 alpha:1.0];
        _separatorView.layer.borderColor = [UIColor lightGrayColor].CGColor;
        _separatorView.layer.borderWidth = 1;
        _separatorView.textAlignment = NSTextAlignmentCenter;
        _separatorView.font = [UIFont systemFontOfSize:16 weight:UIFontWeightHeavy];
        _separatorView.text = @"——";
        _separatorView.userInteractionEnabled = YES;
        
        _separatorDrag = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(didDrag:)];
        [_separatorView addGestureRecognizer:_separatorDrag];
        
        [self.view addSubview:_separatorView];
        
        CGRect tableFrame = self.view.frame;
        tableFrame.origin.y = CGRectGetHeight(mapFrame)+CGRectGetHeight(separatorFrame);
        tableFrame.size.height = 178;
        _tableView = [[UITableView alloc] initWithFrame:tableFrame style:UITableViewStylePlain];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        _tableView.rowHeight = 34;
        
        [self.view addSubview:_tableView];
        
        // prime the location
        [self swirlDidUpdateLocation:[Swirl shared].location];
        
        // subscribe to updates (for location)
        [[Swirl shared] addDelegate:self];
        
    }
    return self;
}

@end
