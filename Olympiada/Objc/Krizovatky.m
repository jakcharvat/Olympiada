//
//  Krizovatky.m
//  Olympiada
//
//  Created by Jakub Charvat on 01.11.2020.
//

#import <Foundation/Foundation.h>


void println(NSString *format, ...) {
    NSString *newFormat = [format stringByAppendingString:@"\n"];
    va_list args;
    va_start(args, format);

    fputs([[[NSString alloc] initWithFormat:newFormat arguments:args] UTF8String], stdout);

    va_end(args);
}


//MARK: - Krizovatka
@interface Krizovatka : NSObject

- (Krizovatka *) initWithId:(int)id;
- (Krizovatka *) initWithId:(int)id jePodVodou:(BOOL)podVodou;
@property int id;
@property(getter=jePodVodou) BOOL podVodou;
@property NSMutableArray<Krizovatka *> *pripojeneKrizovatky;

@end


@implementation Krizovatka

- (Krizovatka *)initWithId:(int)id
{
    return [self initWithId:id jePodVodou:NO];
}

- (Krizovatka *)initWithId:(int)id jePodVodou:(BOOL)podVodou
{
    self = [super init];
    if (self) {
        [self setId:id];
        [self setPodVodou:podVodou];
        [self setPripojeneKrizovatky:[NSMutableArray array]];
    }
    return self;
}


- (NSString *)description
{
    NSString *krizovatky = @"";
    for (Krizovatka *krizovatka in [self pripojeneKrizovatky]) {
        if (krizovatky.length == 0) {
            krizovatky = [krizovatky stringByAppendingFormat:@"%i", krizovatka.id];
        } else {
            krizovatky = [krizovatky stringByAppendingFormat:@" %i", krizovatka.id];
        }
    }
    return [NSString stringWithFormat:@"Krizovatka: %i - %@ - %@", self.id, self.podVodou ? @"YES" : @"NO", krizovatky];
}

@end


//MARK: - BFS Krizovatka
@interface BFSKrizovatka : NSObject

- (BFSKrizovatka *) initWithKrizovatka:(Krizovatka *) krizovatka;
- (BFSKrizovatka *) initWithKrizovatka:(Krizovatka *) krizovatka route:(NSArray<Krizovatka *> *) route distance:(int) distance;

@property Krizovatka *krizovatka;
@property NSArray<Krizovatka *> *routeToCurrent;
@property int distanceToCurrent;

@end


@implementation BFSKrizovatka

- (BFSKrizovatka *)initWithKrizovatka:(Krizovatka *)krizovatka
{
    return [self initWithKrizovatka:krizovatka route:@[] distance:0];
}

- (BFSKrizovatka *)initWithKrizovatka:(Krizovatka *)krizovatka route:(NSArray<Krizovatka *> *)route distance:(int)distance
{
    self = [super init];
    if (self) {
        [self setKrizovatka:krizovatka];
        [self setRouteToCurrent:route];
        [self setDistanceToCurrent:distance];
    }
    return self;
}

@end


//MARK: - BFS
@interface BFS : NSObject

+ (int) getRouteLengthFromIndex:(int)schoolIndex
                        toIndex:(int)houseIndex
                   onKrizovatky:(NSArray<Krizovatka *> *)krizovatky
                          withK:(int)k;

@end


@implementation BFS

+ (int)getRouteLengthFromIndex:(int)schoolIndex
                       toIndex:(int)houseIndex
                  onKrizovatky:(NSArray<Krizovatka *> *)krizovatky
                         withK:(int)k
{
    BFSKrizovatka *initial = [[BFSKrizovatka alloc] initWithKrizovatka:krizovatky[houseIndex]];
    NSMutableArray *queue = [[NSMutableArray alloc] initWithArray:@[initial]];
    NSSet<Krizovatka *> *visitedKrizovatky = [[NSSet alloc] initWithArray:@[initial]];
    
    while (queue.count > 0) {
        BFSKrizovatka *current = queue[0];
        [queue removeObjectAtIndex:0];
        
        int newDistance = current.distanceToCurrent + 1;
        NSArray *newRoute = [current.routeToCurrent arrayByAddingObject:current.krizovatka];
        
        for (Krizovatka *pripojena in current.krizovatka.pripojeneKrizovatky) {
            if (pripojena.id == schoolIndex) return current.distanceToCurrent;
            
            if ([visitedKrizovatky containsObject:pripojena]) continue;
            if (pripojena.podVodou && newDistance > k) continue;
            
            BFSKrizovatka *novaKrizovatka = [[BFSKrizovatka alloc] initWithKrizovatka:pripojena route:newRoute distance:newDistance];
            [queue addObject:novaKrizovatka];
        }
    }
    
    return -1;
}

@end


//MARK: - Krizovatky
@interface Krizovatky : NSObject
+ (void) runPrivalovyDest;
@end


@implementation Krizovatky

+ (void) runPrivalovyDest
{
    int n, m, k;
    scanf("%i %i %i", &n, &m, &k);
    
    NSMutableArray<Krizovatka *> *krizovatky = [NSMutableArray array];
    for (int i = 0; i < n; i ++) {
        int podVodou;
        scanf("%i", &podVodou);
        
        Krizovatka *novaKrizovatka = [[Krizovatka alloc] initWithId:i jePodVodou:podVodou == 1];
        [krizovatky addObject:novaKrizovatka];
    }
    
    
    for (int i = 0; i < m; i ++) {
        int krizovatka1, krizovatka2;
        scanf("%i %i", &krizovatka1, &krizovatka2);
        
        [krizovatky[krizovatka1].pripojeneKrizovatky addObject:krizovatky[krizovatka2]];
        [krizovatky[krizovatka2].pripojeneKrizovatky addObject:krizovatky[krizovatka1]];
    }
    
    
    int length = [BFS getRouteLengthFromIndex:0 toIndex:n-1 onKrizovatky:krizovatky withK:k];
    println(@"%i", length);
}

@end
