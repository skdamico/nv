/* NotesTableView */

#import <Cocoa/Cocoa.h>

@class HeaderViewWithMenu;
@class NoteAttributeColumn;
@class GlobalPrefs;

typedef struct _ViewLocationContext {
	BOOL pivotRowWasEdge;
	id nonRetainedPivotObject;
	float verticalDistanceToPivotRow;
} ViewLocationContext;


@interface NotesTableView : NSTableView {
	IBOutlet NSTextField *controlField;
	NSMutableArray *allColumns;
	
	NSInteger firstRowIndexBeforeSplitResize;
	
	BOOL viewMenusValid;
	BOOL hadHighlightInForeground, hadHighlightInBackground;
	BOOL shouldUseSecondaryHighlightColor;
		
	GlobalPrefs *globalPrefs;
	NSMenuItem *dummyItem;
	HeaderViewWithMenu *headerView;
	NSView *cornerView;
	
	NSDictionary *loadStatusAttributes;
	float loadStatusStringWidth;
	NSString *loadStatusString;

	int affinity;	
}

- (void)noteFirstVisibleRow;
- (void)makeFirstPreviouslyVisibleRowVisibleIfNecessary;

- (ViewLocationContext)viewingLocation;
- (void)setViewingLocation:(ViewLocationContext)ctx;
- (double)distanceFromRow:(int)aRow forVisibleArea:(NSRect)visibleRect;
- (void)scrollRowToVisible:(NSInteger)rowIndex withVerticalOffset:(float)offset;
- (void)selectRowAndScroll:(NSInteger)row;
- (BOOL)objectIsSelected:(id)obj;

- (void)setShouldUseSecondaryHighlightColor:(BOOL)value;
- (void)_setTitleDereferencorState:(BOOL)activeStyle;
- (void)updateTitleDereferencorState;

- (void)reloadDataIfNotEditing;

- (void)restoreColumns;

- (void)updateHeaderViewForColumns;
- (void)editRowAtColumnWithIdentifier:(id)identifier;
- (void)addPermanentTableColumn:(NSTableColumn*)column;
- (IBAction)actionHideShowColumn:(id)sender;
- (IBAction)toggleNoteBodyPreviews:(id)sender;
- (void)setStatusForSortedColumn:(id)item;
- (void)setSortDirection:(BOOL)direction inTableColumn:(NSTableColumn*)tableColumn;
- (NSMenu *)defaultNoteCommandsMenuWithTarget:(id)target;
- (NSMenu *)menuForColumnSorting;
- (NSMenu *)menuForColumnConfiguration:(NSTableColumn *)inSelectedColumn;
- (NoteAttributeColumn*)noteAttributeColumnForIdentifier:(NSString*)identifier;

- (void)incrementNoteSelection:(id)sender;

@end

@interface NSTableView (Private)
- (BOOL)_shouldUseSecondaryHighlightColor;
- (void)_sizeRowHeaderToFitIfNecessary;

//10.3 only
- (void)_sizeToFitIfNecessary;
@end
