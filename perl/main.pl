package Heap;
use strict;
use warnings;

sub new {
    my $class = shift;
    my $capacity = shift;

    return bless {
        size => 0,
        capacity => $capacity,
        data => [ map { 0 } ( 0 .. $capacity + 1 ) ],
    } => $class;
}

sub parent_idx {
    my $self = shift;
    my $pos = shift;
    return int($pos / 2);
}

sub left_idx {
    my $self = shift;
    my $pos = shift;
    return $pos * 2;
}

sub right_idx {
    my $self = shift;
    my $pos = shift;
    return $pos * 2 + 1;
}

sub is_leaf {
    my $self = shift;
    my $pos = shift;

    return $self->left_idx($pos) > $self->{size};
}

sub swap {
    my $self = shift;
    my ($a, $b) = @_;

    ($self->{data}[$a], $self->{data}[$b]) = ($self->{data}[$b], $self->{data}[$a]);
}

sub push {
    my $self = shift;
    my $item = shift;

    if ( $self->{size} >= $self->{capacity} ) {
        die "pushing into a fill container";
    }

    $self->{size} += 1;
    my $cur = $self->{size};

    $self->{data}[$cur] = $item;
    while ( $cur > 1 && $self->{data}[$cur] < $self->{data}[ $self->parent_idx($cur) ] ) {
        $self->swap( $cur, $self->parent_idx($cur) );
        $cur = $self->parent_idx( $cur );
    }
}

sub percolate {
    my $self = shift;
    my $pos = shift;

    return if $self->is_leaf($pos);

    my $cur = $self->{data}[$pos];
    my $left = $self->{data}[ $self->left_idx($pos) ];
    my $right = @{$self->{data}} > $self->right_idx($pos) ? $self->{data}[ $self->right_idx($pos) ] : undef;

    if ( $left < $cur || ((defined $right) && $right < $cur) ) {
        if ( !(defined $right) || $left < $right ) {
            $self->swap( $pos, $self->left_idx($pos) );
            $self->percolate( $self->left_idx($pos) );
        } else {
            $self->swap( $pos, $self->right_idx($pos) );
            $self->percolate( $self->right_idx($pos) );
        }
    }
}

sub pop {
    my $self = shift;

    if ( $self->{size} < 1 ) {
        die "empty heap";
    }

    my $res = $self->{data}[1];
    $self->{data}[1] = $self->{data}[ $self->{size} ];
    $self->{size} -= 1;
    $self->percolate( 1 );

    return $res;
}

package main;
use strict;
use warnings;

use Time::HiRes qw/time/;

sub main {
    my $heap_max = 10_000;
    my $heap = Heap->new($heap_max);

    my $time = 0;
    my $total = 5_000_000;

    my $start = time();

    for my $idx (0..$total) {
        if ($heap->{size} >= $heap_max) {
            $time = $heap->pop();
        }

        my $diff = $idx % 2 == 0 ? 2 :
                   $idx % 3 == 0 ? 5 : 20;

        $heap->push($time + $diff);
    }

    while ($heap->{size} > 0) {
        $time = $heap->pop();
    }

    my $elapsed = (time() - $start) * 1000;

    printf("PERL simualtion result: %d, runtime: %.2f ms\n", $time, $elapsed);
}

__PACKAGE__->main();
