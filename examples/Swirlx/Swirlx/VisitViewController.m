// =====================================================================================================================
// VisitViewController.
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <Swirl/Swirl.h>
#import "VisitViewController.h"

@interface VisitViewController ()
@property (nonatomic) NSArray<SWRLVisit*>*  visits;
@end

@implementation VisitViewController

- (void) updateVisits:(NSArray<SWRLVisit *>*)visits {
    _visits = visits;
    [self.tableView reloadData];
}

- (void) visitManager:(SWRLVisitManager *)manager didBeginVisit:(SWRLVisit *)visit {
    [self updateVisits:manager.activePlacementVisits];
}

- (void) visitManager:(SWRLVisitManager *)manager didUpdateDwellForVisit:(SWRLVisit *)visit {
    [self updateVisits:manager.activePlacementVisits];
}

- (void) visitManager:(SWRLVisitManager *)manager didEndVisit:(SWRLVisit *)visit {
    [self updateVisits:manager.activePlacementVisits];
}

- (instancetype)init {
    if ((self = [super initWithStyle:UITableViewStylePlain]) != nil) {
        self.tableView.rowHeight = 100;
        SWRLVisitManager *visitManager = [[Swirl shared] findDelegateOfClass:[SWRLVisitManager class]];
        [self updateVisits:visitManager.activePlacementVisits];
        [[Swirl shared] addDelegate:self];
    }
    return self;
}

- (void) dealloc {
    [[Swirl shared] removeDelegate:self];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _visits.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"default"];
    if (cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"default"];
    
    SWRLVisit *visit = _visits[indexPath.row];
    cell.textLabel.font = [UIFont systemFontOfSize:14.0];
    cell.textLabel.text = visit.location.description;
    cell.textLabel.textColor = [UIColor blackColor];
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.lineBreakMode = NSLineBreakByWordWrapping;
    cell.detailTextLabel.font = [UIFont systemFontOfSize:14.0];
    cell.detailTextLabel.numberOfLines = 0;
    cell.detailTextLabel.lineBreakMode = NSLineBreakByWordWrapping;
    cell.detailTextLabel.text = visit.location.signal.description;
    cell.detailTextLabel.textColor = [UIColor grayColor];
    cell.accessoryType = UITableViewCellAccessoryNone;
    
    return cell;
}

@end
