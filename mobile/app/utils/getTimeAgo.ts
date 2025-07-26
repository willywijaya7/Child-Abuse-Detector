export function getTimeAgo(isoTimestamp: string): string {
  try {
    if (!isoTimestamp) return '-';

    const now = new Date();
    const inputDate = new Date(isoTimestamp);

    if (isNaN(inputDate.getTime())) return '-'; // Invalid date

    const diffMs = now.getTime() - inputDate.getTime();
    const diffSec = Math.floor(diffMs / 1000);
    const diffMin = Math.floor(diffSec / 60);
    const diffHour = Math.floor(diffMin / 60);
    const diffDay = Math.floor(diffHour / 24);

    if (diffSec < 60) return 'Just now';
    if (diffMin < 60) return `${diffMin} minute${diffMin > 1 ? 's' : ''} ago`;
    if (diffHour < 24) return `${diffHour} hour${diffHour > 1 ? 's' : ''} ago`;
    return `${diffDay} day${diffDay > 1 ? 's' : ''} ago`;
  } catch (e) {
    console.error('Failed to parse timestamp:', e);
    return '-';
  }
}
